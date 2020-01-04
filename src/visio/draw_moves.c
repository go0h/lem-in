/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:41:56 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/29 23:00:35 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		paint_ants(t_visual *vis, t_ant *army, int meat)
{
	int		radius;

	event(vis);
	if (vis->quit)
	{
		radius = vis->radius / 3 > 2 ? vis->radius / 3 : 3;
		while (meat--)
		{
			filledCircleColor(vis->render, army->x, army->y, radius,\
			army->color.color);
			army = army->next;
		}
	}
}

static void		set_ants_dislocation(t_ant *army, int meat)
{
	while (meat--)
	{
		army->x = army->path->vrx->x;
		army->y = army->path->vrx->y;
		army->dx = army->path->next->vrx->x - army->x;
		army->dy = army->path->next->vrx->y - army->y;
		army = army->next;
	}
}

static void		move_ants(t_ant *army, int meat)
{
	while (meat--)
	{
		army->x += army->dx / STEPS;
		army->y += army->dy / STEPS;
		army = army->next;
	}
}

void			draw_move_ants(t_lem *lem, t_ant *army, int meat)
{
	int		i;

	set_ants_dislocation(army, meat);
	i = STEPS > 0 ? STEPS : 0;
	while (i--)
	{
		draw_graph(lem, lem->listpath, 0);
		move_ants(army, meat);
		paint_ants(lem->vis, army, meat);
		draw_counters(lem, army, meat);
		SDL_RenderPresent(lem->vis->render);
		if (!lem->visual)
			break ;
	}
	usleep(lem->vis->delay * 3);
}
