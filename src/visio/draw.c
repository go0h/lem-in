/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:38:29 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/30 14:22:56 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			draw_graph(t_lem *lem, t_listpath *listpath, char f)
{
	t_vrx	*vrx;

	event(lem->vis);
	if (!(lem->visual = lem->vis->quit))
		return ;
	SDL_SetRenderDrawColor(lem->vis->render, 0, 0, 0, 0);
	SDL_RenderClear(lem->vis->render);
	vrx = lem->vrx;
	draw_edges(lem->vis, vrx);
	while (vrx)
	{
		draw_vertex(lem->vis, vrx, 'b');
		vrx = vrx->next;
	}
	draw_listpath(lem->vis, listpath);;
	f ? SDL_RenderPresent(lem->vis->render) : 0;
	usleep(lem->vis->delay * 3);
}

static int		ft_wait(t_visual *vis, int time)
{
	int i;

	i = 0;
	while (i++ < time)
	{
		while (SDL_PollEvent(&vis->e))
		{
			if (vis->e.type == SDL_QUIT || (vis->e.type == SDL_KEYDOWN\
			&& vis->e.key.keysym.sym == SDLK_ESCAPE))
			{
				vis->quit = 0;
				return (vis->quit);
			}
			else if (vis->e.type == SDL_KEYDOWN)
			{
				if (vis->e.key.keysym.sym == SDLK_f)
					return (-1);
			}
		}
		usleep(1000);
	}
	return (1);
}

static void		wait2go(t_visual *vis, SDL_Texture *text2,\
				SDL_Rect rect1, SDL_Rect rect2)
{
	while (1)
	{
		SDL_SetRenderDrawColor(vis->render, 0, 0, 0, 0);
		SDL_RenderClear(vis->render);
		texture2render(vis->render, vis->texture, rect1);
		if (ft_wait(vis, 500) < 1)
			break ;
		texture2render(vis->render, text2, rect2);
		if (ft_wait(vis, 500) < 1)
			break ;
	}
}

void			draw_intro(t_lem *lem)
{
	t_color		c;
	SDL_Texture *press;
	SDL_Rect	welcome;
	SDL_Rect	start;

	c.color = ~0;
	lem->vis->texture = text2texture(lem->vis->render, lem->vis->font,\
	"Welcome to Lem-in", c);
	if (!lem->vis->texture)
		ft_exit(&lem, 0);
	press = text2texture(lem->vis->render, lem->vis->font,\
	"Press F to start", c);
	if (!press)
		ft_exit(&lem, 0);
	welcome = get_rectangle(WIN_WIDTH / 2, INDENT, WIN_WIDTH / 4,\
	WIN_HEIGHT / 2 - INDENT);
	start = get_rectangle(300, 50, WIN_WIDTH / 2 - 150,\
	WIN_HEIGHT / 2 + INDENT);
	wait2go(lem->vis, press, welcome, start);
	SDL_DestroyTexture(lem->vis->texture);
	lem->vis->texture = NULL;
	SDL_DestroyTexture(press);
}

void			draw_outro(t_lem *lem)
{
	t_color		c;
	SDL_Texture *press;
	SDL_Rect	welcome;
	SDL_Rect	start;

	c.color = ~0;
	SDL_SetRenderDrawColor(lem->vis->render, 0, 0, 0, 0);
	lem->vis->texture = text2texture(lem->vis->render, lem->vis->font,\
	"Thanks for your evaluation", c);
	if (!lem->vis->texture)
		ft_exit(&lem, 0);
	press = text2texture(lem->vis->render, lem->vis->font,\
	"Press F to respect", c);
	if (!press)
		ft_exit(&lem, 0);
	welcome = get_rectangle(WIN_WIDTH - (INDENT * 2), INDENT, INDENT,\
	WIN_HEIGHT / 2 - INDENT);
	start = get_rectangle(400, 50, WIN_WIDTH / 2 - 200,\
	WIN_HEIGHT / 2 + INDENT);
	wait2go(lem->vis, press, welcome, start);
	SDL_DestroyTexture(lem->vis->texture);
	lem->vis->texture = NULL;
	SDL_DestroyTexture(press);
}
