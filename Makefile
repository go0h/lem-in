# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astripeb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 15:47:32 by pcredibl          #+#    #+#              #
#    Updated: 2020/01/04 14:32:09 by astripeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= lem-in

#LIBFT_DIRS
LIB_DIR			:= ./libft
LIBFT			:= libft.a

#PROJECT_DIRS
INC_DIR			:= ./include
OBJ_DIR			:= ./obj
SRC_DIR			:= ./src/algorithm
SRC_VIS_DIR		:= ./src/visio

LIBS			= -L $(LIB_DIR) -lft

CC				:= gcc
CFLAGS			= -Wall -Wextra -Werror

LFLAGS			= -I $(LIB_DIR)/inc -I $(INC_DIR)

#SDL2_DIRS
CFLAGS			+= $(shell sdl2-config --cflags)
LIBS			+= $(shell sdl2-config --libs) -lSDL2_gfx -lSDL2_ttf -lm

HEADERS			:= lem_in.h visual.h

SRC 			:= create_lem.c lem_in.c add_edges_to_lem.c check_lem.c\
				adj_func.c utility.c ft_exit.c validation.c\
				direction.c dfs.c bfs.c path_func.c\
				queue.c suurballe.c renovation.c free_elem.c\
				tactical_moves.c ants.c listpath_func.c

SRC_VIS			:= init.c order_graph.c draw_graph_funcs.c\
				draw.c fonts_funcs.c draw_moves.c counters.c

OBJ_LEM			:= $(SRC:.c=.o)
OBJ_VIS			:= $(SRC_VIS:.c=.o)
OBJ				:= $(OBJ_LEM) $(OBJ_VIS)

vpath %.c $(SRC_DIR) $(SRC_VIS_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR) $(SDL2_INC)
vpath %.a $(LIB_DIR)

GREEN 			:= \033[0;32m
RED 			:= \033[0;31m
RESET			:= \033[0m

all: lib $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(SDL_LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ)) $(LIBS) -o $@
	echo "$(GREEN)DONE ✅$(RESET)"

$(OBJ_VIS):%.o:%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

$(OBJ_LEM):%.o:%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(OBJ_DIR)/$@ -c $<
	echo "$(GREEN)$@ was created$(RESET)"

lib:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)
	echo "$(RED)objects files was deleted$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME)
	echo "$(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.SILENT: all $(NAME) $(OBJ) $(OBJ_DIR) $(LIBFT) clean fclean re lib

.PHONY: clean fclean re all libftprintf
