/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:57:27 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/30 14:20:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libftprintf.h"
# include "visual.h"
# include <stdio.h>

# define START 1
# define END 2
# define COMMENT 3

# define ON 1
# define OFF 0

# define MAX_INT 2147483647

# define NORMAL_EXIT 99
# define INVALID_INPUT 100
# define START_END 101
# define DOUBLE_VRX 102
# define ONE_COMPONENT 103
# define SDL_INIT_ERROR 104
# define SDL_WIN_ERROR 105
# define USAGE 106
# define INVALID_OPTION 107

typedef struct			s_adj
{
	char				*name;
	struct s_adj		*next;
	struct s_vrx		*vrx;
	char				weight;
	char				dir;
}						t_adj;

typedef struct			s_lem
{
	char				*map;
	struct s_vrx		*vrx;
	int					ant_c;
	int					vert_c;
	int					edge_c;
	struct s_listpath	*listpath;
	struct s_visual		*vis;
	char				visual;
	char				without_map;
	char				design_map;
}						t_lem;

typedef struct			s_vrx
{
	struct s_adj		*adj;
	char				*name;
	int					x;
	int					y;
	struct s_vrx		*next;
	struct s_vrx		*anc;
	char				type;
	char				visit;
	char				sep;
}						t_vrx;

typedef struct			s_queue
{
	struct s_vrx		*vrx;
	char				weight;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_listpath
{
	int					path_len;
	struct s_path		*path;
	struct s_listpath	*next;
	union u_color		color;
}						t_listpath;

typedef struct			s_path
{
	struct s_vrx		*vrx;
	struct s_path		*next;
}						t_path;

typedef struct			s_ant
{
	int					serial_number;
	struct s_path		*path;
	struct s_ant		*next;
	struct s_ant		*prev;
	float				dx;
	float				dy;
	float				x;
	float				y;
	union u_color		color;
}						t_ant;

void					ft_exit(t_lem **lem, int err);

void					options(int ac, char **av, t_lem *lem);

/*
** CREATE MAIN STRUCTURE FUNCTIONS
*/

t_lem					*create_lem(int fd);

void					ft_edge(t_lem *lem, char **lines);

t_adj					*ft_addlst(t_adj *adj, char *elem, char wght);

void					add_adj(t_lem *lem, char **v);

void					add_link_adj_to_vrx(t_lem *lem);

void					ft_del_lem(t_lem **lem_to_del);

/*
** VALIDATION FUNCTIONS
*/

char					vrx_info(char *s);

void					check_lem(t_lem *lem);

void					is_two_vert(char **vertexes);

int						ft_validate_vrx(char **map);

int						ft_validate_edge(char **map);

int						exist_vertex(t_vrx *vrx, char **vertexes);

int						invalid_com(char *str);

/*
** DIRECTIONS FUNCTIONS
*/

t_vrx					*get_vrx(t_vrx *vrx, char *name);

t_adj					*get_adj(t_adj *adj, char *name);

void					change_dir(t_vrx *vrx, char *end, char dir);

void					redirect_lem(t_path *path, char tumbler);

void					renovation_one_to_two_dir(t_lem *lem);

void					full_renovation_lem(t_lem *lem);

void					unvisit(t_vrx *vertex);

/*
** SUURBALLE ALGORITHM FUNCTIONS
*/

t_path					*bfs(t_lem *lem);

int						dfs(t_lem *lem, t_vrx *vrx);

t_queue					*new_queue(t_vrx *vrx, char weight);

void					add_queue(t_queue **queue, t_vrx *vrx, char weight);

int						free_queue(t_queue **queue);

void					del_one_queue(t_queue **queue);

int						suurballe(t_lem *lem, t_listpath **listpath,\
						int min_paths);

void					find_optimal_path(t_lem *lem, t_ant *army);

/*
** PATHS FUNCTIONS
*/

void					ft_free_path(t_listpath **listpath_to_del);

void					ft_free_one_path(t_path **path_to_del);

int						add_listpath(t_listpath **listpath, t_path *path);

int						add_path_to_begin(t_path **begin, t_vrx *vrx);

int						path_len(t_path *path);

void					renovate_listpath(t_listpath *listpath);

/*
** ANTS FUNCTIONS
*/

void					dissolve_army(t_ant **first_soldier);

void					first_soldier_commission(t_ant **army);

void					soldiers_commission(t_ant **army);

t_ant					*new_soldier(int serial_number);

t_ant					*create_army(int number_of_soldiers);

int						routing(t_listpath *paths, t_ant *army);

void					tactical_moves(t_lem *lem, t_ant *army,\
						t_listpath *listpath);

void					offensive(t_lem *lem, t_ant *army);

void					visit_listpath(t_listpath *listpath);

int						count_paths(t_listpath *listpath);

/*
** VISIO FUNCTIONS
*/

void					initilize_visio(t_lem *lem);

void					drop_visio(t_visual **vis);

void					margin_vertex(t_lem *lem);

void					event(t_visual *vis);

void					design_map(t_lem *lem);

/*
** DRAW FUNCTIONS
*/

void					draw_intro(t_lem *lem);

void					draw_graph(t_lem *lem, t_listpath *listpath, char f);

void					draw_vertex(t_visual *vis, t_vrx *vrx, char c);

void					draw_edge(t_visual *vis, t_vrx *from, t_vrx *to,\
						char c);

void					draw_edges(t_visual *vis, t_vrx *vrx);

void					draw_listpath(t_visual *vis, t_listpath *lp);

void					draw_path(t_visual *vis, t_path *path);

void					draw_move_ants(t_lem *lem, t_ant *army, int meat);

void					draw_outro(t_lem *lem);

void					set_path_color(t_listpath *listpath);

void					draw_counters(t_lem *lem, t_ant *army, int meat);

/*
** VISIO UTILITY
*/

SDL_Rect				get_rectangle(int width, int height, int x, int y);

SDL_Texture				*text2texture(SDL_Renderer *rend, TTF_Font *font,\
						char *str, t_color c);

void					texture2render(SDL_Renderer *rend, SDL_Texture *text,\
						SDL_Rect rect);

#endif
