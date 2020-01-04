case $1 in
    1)
        MAP=--flow-one
        ;;
    10)
        MAP=--flow-ten
        ;;
    1000)
        MAP=--flow-thousand
        ;;
    big)
        MAP=--big
        ;;
    bigs)
        MAP=--big-superposition
        ;;
    *)
        :;
esac

if [[ -n $MAP ]]; then
    ./generatorE $MAP > map
fi

tail -n 1 map
./lem-in < map > out
./verifier < out

