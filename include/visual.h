/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:37:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/29 23:06:00 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include <SDL_ttf.h>
# include <math.h>

# ifdef __linux__
	# define WIN_HEIGHT 800
	# define WIN_WIDTH 1000
	# define INDENT 100
# else
	# define WIN_HEIGHT 1200
	# define WIN_WIDTH 1600
	# define INDENT 100
# endif

/*
** VERTEX COLORS (RGBA - int)
*/

# define V_STRT				4280221470
# define V_END 				4278190335
# define V_RED 				4278190335
# define V_BLUE				4284743680
# define V_GREEN 			4278228480
# define V_YELLOW 			4278255615
# define V_SIMP				4284751390

/*
** EDGE COLORS (RGBA - int)
*/

# define E_BLUE 			4284743680
# define E_RED 				2516582655
# define E_GREEN 			2516620800
# define E_YELLOW 			2516647935

/*
** ANT COLORS (RGBA - int)
*/

# define A_MOCCASIN 		4290110719
# define A_DARKTURQUOISE	4291939840
# define A_BLUE				4294901760
# define A_CYAN				4294967040
# define A_LAWNREEN			4278254716
# define A_DARJKHAKI		4285249469
# define A_YELLOW			4278255615
# define A_INDIANRED		4284243149
# define A_FIREBRICK		4280427186
# define A_DARKORANGE		4278226175
# define A_MAGENTA 			4294902015

# define STEPS				75

typedef union				u_color
{
	struct					s_rgb
	{
		unsigned char		red:8;
		unsigned char		green:8;
		unsigned char		blue:8;
		unsigned char		alpha:8;
	}						t_rgb;
	unsigned int			color;
}							t_color;

typedef struct				s_visual
{
	SDL_Window				*win;
	SDL_Renderer			*render;
	SDL_Texture				*texture;
	SDL_Event				e;
	TTF_Font				*font;
	char					quit;
	int						radius;
	int						line_w;
	int						delay;
	char					pass;
}							t_visual;

void						ft_free_visual(t_visual **vis);

#endif
