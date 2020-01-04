/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:05:36 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/29 23:01:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		first_pass(t_lem *lem, int min_paths)
{
	t_path		*path;

	while (min_paths-- && (path = bfs(lem)))
	{
		if (lem->visual && !lem->vis->pass)
			draw_path(lem->vis, path);
		redirect_lem(path, OFF);
		if (!dfs(lem, lem->vrx))
		{
			redirect_lem(path, ON);
			unvisit(lem->vrx);
			break ;
		}
		unvisit(lem->vrx);
		ft_free_one_path(&path);
	}
}

int				suurballe(t_lem *lem, t_listpath **listpath, int min_paths)
{
	int			i;
	t_path		*path;

	path = NULL;
	first_pass(lem, min_paths);
	renovation_one_to_two_dir(lem);
	unvisit(lem->vrx);
	i = 0;
	while (i < min_paths && (path = bfs(lem)))
	{
		redirect_lem(path, OFF);
		if (!add_listpath(listpath, path))
		{
			ft_free_path(listpath);
			ft_free_one_path(&path);
			ft_exit(&lem, MALLOC_FAILURE);
		}
		++i;
		visit_listpath(*listpath);
	}
	full_renovation_lem(lem);
	lem->visual && !lem->vis->pass ? draw_graph(lem, *listpath, 1) : 0;
	return (i);
}

static void		search_optimal_count_of_paths(t_lem *lem, t_listpath *paths,\
				int min_steps, t_ant *army)
{
	int			min_paths;
	int			steps;

	min_paths = 1;
	steps = MAX_INT;
	while (min_steps <= steps && lem->ant_c > count_paths(paths))
	{
		min_paths++;
		lem->visual && !lem->vis->pass ? draw_graph(lem, NULL, 1) : 0;
		if (suurballe(lem, &paths, min_paths) != min_paths)
			break ;
		steps = routing(paths, army);
		if (min_steps > steps)
		{
			ft_free_path(&lem->listpath);
			min_steps = steps;
			lem->listpath = paths;
			paths = NULL;
		}
		else if (min_steps == steps)
			ft_free_path(&paths);
	}
	ft_free_path(&paths);
}

void			find_optimal_path(t_lem *lem, t_ant *army)
{
	int			min_steps;
	t_listpath	*listpath;

	listpath = NULL;
	suurballe(lem, &lem->listpath, 1);
	min_steps = routing(lem->listpath, army);
	search_optimal_count_of_paths(lem, listpath, min_steps, army);
	ft_free_path(&listpath);
	renovate_listpath(lem->listpath);
	if (lem->visual)
	{
		!lem->vis->pass ? draw_graph(lem, lem->listpath, 1) : 0;
		set_path_color(lem->listpath);
	}
}
