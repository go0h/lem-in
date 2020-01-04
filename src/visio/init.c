/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:27:26 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/29 23:06:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_visual	*new_visio(void)
{
	t_visual	*vis;

	if (!(vis = (t_visual*)malloc(sizeof(t_visual))))
		return (NULL);
	vis->win = NULL;
	vis->render = NULL;
	vis->texture = NULL;
	vis->quit = 1;
	vis->delay = 0;
	vis->pass = 0;
	ft_bzero((void*)&vis->e, 56);
	return (vis);
}

void			drop_visio(t_visual **vis)
{
	if (vis && *vis)
	{
		SDL_DestroyRenderer((*vis)->render);
		SDL_DestroyTexture((*vis)->texture);
		SDL_DestroyWindow((*vis)->win);
		TTF_CloseFont((*vis)->font);
		(*vis)->win = NULL;
		SDL_Quit();
		free(*vis);
		*vis = NULL;
	}
}

void			initilize_visio(t_lem *lem)
{
	if (!(lem->vis = new_visio()))
		ft_exit(&lem, MALLOC_FAILURE);
	if ((SDL_Init(SDL_INIT_VIDEO)) < 0)
		ft_exit(&lem, SDL_INIT_ERROR);
	if (TTF_Init() == -1)
		ft_exit(&lem, SDL_INIT_ERROR);
	else
	{
		lem->vis->win = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!lem->vis->win)
			ft_exit(&lem, SDL_WIN_ERROR);
		lem->vis->render = SDL_CreateRenderer(lem->vis->win, -1, \
		SDL_RENDERER_SOFTWARE);
		if (lem->vis->render == NULL)
			ft_exit(&lem, 0);
		lem->vis->radius = ft_min(WIN_HEIGHT, WIN_WIDTH) / (lem->vert_c * 3);
		lem->vis->radius = ft_max(lem->vis->radius, 2);
		if (!(lem->vis->font = TTF_OpenFont("./fonts/PTC55F.ttf", 20)))
			ft_exit(&lem, 0);
		lem->vis->line_w = ft_max(lem->vis->radius / 3, 2);
		lem->vis->delay = ft_min(2500000 / lem->edge_c, 200000);
		lem->design_map ? design_map(lem) : 0;
	}
}

void			event(t_visual *vis)
{
	while (SDL_PollEvent(&vis->e) != 0)
	{
		if (vis->e.type == SDL_QUIT)
			vis->quit = 0;
		else if (vis->e.type == SDL_KEYDOWN)
		{
			if (vis->e.key.keysym.sym == SDLK_ESCAPE)
				vis->quit = 0;
			if (vis->e.key.keysym.sym == SDLK_s)
				vis->delay *= 1.25;
			if (vis->e.key.keysym.sym == SDLK_f)
				vis->delay /= 1.25;
			if (vis->e.key.keysym.sym == SDLK_p)
				vis->pass = 1;
			vis->delay = ft_min(vis->delay, 250000);
			vis->delay = ft_max(vis->delay, 1);
		}
	}
}
