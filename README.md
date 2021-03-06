# lem-in

<a href="https://github.com/go0h/lem-in/blob/master/lem-in.en.pdf">SUBJECT<a>

Программа предназначена для нахождения максимального количество вершинно-независимых путей, для перемещения из точки ```A``` в точку ```B``` 'муравьев' за наименьшее количество ходов, при условии, что за один ход 'муравьи' могут пройти в соседнюю вершину, но не могут передвигаться по несколько штук по одному и тому же ребру, а так же не могут находиться одновременно в одной вершине (за исключением вершины-старт и вершины-финиш).

Программе на вход подается информация о графе (муравейнике):
 - количество 'муравьев';
 - название вершин и их координаты. Командами ```##start``` и ```##end``` указываются начальная и конечная вершина пути.
 - ребра, соединяющие вершины.

### Входные данные
Файл с входными данными подается через терминал следующим образом: ```./lem-in < 'map_file'```. Файл с картой выглядит следующим образом:

```
100
##start
A 0 2
B 1 0
#comment
C 3 0
D 4 2
E 2 2
F 3 4
G 5 4
#another comment
##end
H 6 2
A-B
A-E
B-C
C-D
D-E
#comment №3
D-H
D-F
E-F
F-G
G-H
```
Сначала идет количество муравьев (в приведенном примере 100). Далее идет описание вершин (ее название + ее координаты (х и у)). 
Команды ##start и ##end означают, что после них будет дана вершина-старт и вершина-финиш соответственно. После вершин идет информация
о том, какие вершины соединены, в виде ```D-H```. На этом обязательная информации по карте заканчивается. В файле на любой строчке могут располагаться комментарии (строка с комментарием обязана начинаться с '#', невалидные команды, наподобие ```##falseCommand```, тоже должны восприниматься как комментарии).  

### Валидация карты  
На этапе валидации карты проверяются следующие условия:  
1) Количество муравьев не отрицательное.  
2) Ровно по одной вершине обознаены как старт и как финиш.  
3) Есть хотя бы один путь соединяющий старт и финиш, т.е. граф является связным.  
4) нет вершин с одинаковыми названиями.  
5) Нет вершин с одинаковыми координатами (одинаковые и х и у).  
6) Ребра соединяют только существующие вершины.  
7) Нет вершин, начинающихся с 'L' и содержащих дефис (такие вершины затрудняют просмотр решения).  
Граф может иметь мульти-ребра (2 вершины могут быть соединены более чем 1 ребром) и петли (ребра, соединяющие вершину саму с собой).
Ошибок в работе алгоритма данные ребра не вызовут.

### Алгоритм  
Задача сводится к поиску вершинно-непересекающихся путей между стартом и финишем. Для поиска таких путей используется алгоритм Суурбалле. Более подробно о данном алгоритме можно прочесть по [ссылке](http://www.macfreek.nl/memory/Disjoint_Path_Finding). небольшие изменения в работе алгоритма:  
1) Для поиска кратчайшеого пути используется поиск в ширину.  
2) Вместо физического разделения вершин, учавствующих в пути, на vertex-in и vertex-out, используется пометка данных вершин флагом с соответствующим изменением поведения алгоритма при поиске пути помеченной данным флагом.
При поиске решения алгоритм Суурбалле используется в цикле по следующему принципу:  
1) Сначала находим первый путь (он существует всегда, так как мы предварительно проверили существование пути между стартом и финишем). Расчитываем сколько ходов потребуется чтобы провести всех муравьев через этот путь. Запоминаем количество ходов.  
2) Пытаемся найти очередной путь. Тут существует 4 варианта:  
    а) Еще один путь не найден. В этом случае мы нашли все существующие пути между стартом и финишем, и оптимально использовать все найденные пути.  
    б) Путь найден, но рассчитанное количество ходов больше чем при использовании меньшего количества пути. В этом случае прекращаем дальнейший поиск и используем пути, найденные в предыдущей итерации.  
    в) Путь найден, но количество путей превышает количество муравьев. В этом случае прекращаем дальнейший поиск и используем пути, найденные в предыдущей итерации.  
    г) Путь найден, и расчитанное количество ходов **не** больше, чем при использовании меньшего количества путей. В этом случае еще раз повторяем шаг (2).  
По выходу из цикла у нас будет оптимальное решение.  

### Вывод
Перед решением необходимо вывести карту, полученную на вход.
Решение выводится в следующем формате:  
```
L1-2
L1-3 L2-2
L1-1 L2-3 L3-2
L2-1 L3-3
L3-1

```
где каждая новая строка - новый ход, после 'L' идет номер муравья, а после тире - название вершины, куда муравей пошел в этом ходу. Муравьи, дошедшие до финиша пропадают из вывода со следующего хода.

### Флаги  
в программе реализованы следующие флаги:  
```
Usage:
./lem-int [-m, -v, -d] < map
    [-m] - print decision without input map
    [-v] - turn on visualisation
    [-d] - design map
```
**-m** - распечатывает решение без печати карты, поступившей на вход.  
**-v** - визуализация. Визуализация реализована с помощью графической библиотеки SDL2. Для корректной работы в UNIX-подобных системах необходимо установить следующие библиотеки:  
```
SDL2
SDL2_ttf
SDL2_gfx
```
**-d** - дизайн карты. Чаще всего нужен для корректного отображения карт очень больших размеров, карт, где координаты вершин имеют очень большой разброс, или же назначены случайным образом и отрисовке по координатам сливаются во что-то неудобное для визуального восприятия.
Данный режим принудительно назначает всем вершинам координаты по порядку, чтобы они вписались в квадрат. Старт и финиш выносятся сверху и снизу данного квадрата.  
