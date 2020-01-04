/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_graph_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:47:13 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/07 00:23:42 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		draw_vertex(t_visual *vis, t_vrx *vrx, char c)
{
	if (c == 'r')
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius, V_RED);
	else if (c == 'b')
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius, V_BLUE);
	else if (c == 'g')
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius, V_GREEN);
	else if (c == 'y')
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius, V_YELLOW);
	if (vrx->type == START)
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius - 3, V_STRT);
	else if (vrx->type == END)
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius - 3, V_END);
	else if (!vrx->type)
		filledCircleColor(vis->render, vrx->x, vrx->y, vis->radius - 3, V_SIMP);
}

void		draw_edge(t_visual *vis, t_vrx *from, t_vrx *to, char c)
{
	if (c == 'r')
	{
		thickLineColor(vis->render, from->x, from->y, to->x, to->y,\
		vis->line_w * 2, E_RED);
	}
	else if (c == 'b')
	{
		thickLineColor(vis->render, from->x, from->y, to->x, to->y,\
		vis->line_w, E_BLUE);
	}
	else if (c == 'g')
	{
		thickLineColor(vis->render, from->x, from->y, to->x, to->y,\
		vis->line_w * 2, E_GREEN);
	}
	else
	{
		thickLineColor(vis->render, from->x, from->y, to->x, to->y,\
		vis->line_w * 2, E_YELLOW);
	}
}

void		draw_edges(t_visual *vis, t_vrx *vrx)
{
	t_adj		*adj;

	while (vrx)
	{
		adj = vrx->adj;
		while (adj)
		{
			draw_edge(vis, vrx, adj->vrx, 'b');
			adj = adj->next;
		}
		vrx = vrx->next;
	}
}

void		draw_listpath(t_visual *vis, t_listpath *lp)
{
	t_path		*path;

	while (lp)
	{
		path = lp->path;
		while (path->next)
		{
			draw_edge(vis, path->vrx, path->next->vrx, 'g');
			draw_vertex(vis, path->vrx, 'g');
			path = path->next;
		}
		draw_vertex(vis, path->vrx, 'g');
		lp = lp->next;
	}
}

void		draw_path(t_visual *vis, t_path *path)
{
	while (path->next)
	{
		event(vis);
		if (!vis->quit || vis->pass)
			return ;
		if (path->vrx->sep && path->next->vrx->sep)
			draw_edge(vis, path->vrx, path->next->vrx, 'r');
		else
			draw_edge(vis, path->vrx, path->next->vrx, 'y');
		usleep(vis->delay);
		draw_vertex(vis, path->vrx, 'y');
		draw_vertex(vis, path->next->vrx, 'y');
		path = path->next;
		SDL_RenderPresent(vis->render);
	}
	usleep(vis->delay * 3);
}
