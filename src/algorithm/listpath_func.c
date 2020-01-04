/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listpath_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:14:11 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/29 16:28:07 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_listpath	*min_path(t_listpath *paths)
{
	int			min_len;
	t_listpath	*min_len_path;

	min_len = MAX_INT;
	min_len_path = NULL;
	while (paths)
	{
		if (paths->path_len < min_len)
		{
			min_len = paths->path_len;
			min_len_path = paths;
		}
		paths = paths->next;
	}
	min_len_path->path_len += 1;
	return (min_len_path);
}

static t_listpath	*new_listpath(t_path *path)
{
	t_listpath	*listpath_t;

	if (!(listpath_t = (t_listpath*)malloc(sizeof(t_listpath))))
		return (NULL);
	listpath_t->path = path;
	listpath_t->path_len = path_len(path);
	listpath_t->next = NULL;
	listpath_t->color.color = 0;
	return (listpath_t);
}

int					add_listpath(t_listpath **listpath, t_path *path)
{
	t_listpath	*temp;

	if (!*listpath)
	{
		if (!(*listpath = new_listpath(path)))
		{
			ft_free_one_path(&path);
			return (0);
		}
	}
	else
	{
		temp = *listpath;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = new_listpath(path)))
		{
			ft_free_one_path(&path);
			return (0);
		}
	}
	return (1);
}

int					routing(t_listpath *paths, t_ant *army)
{
	t_listpath	*mpath;
	int			steps;
	int			transit_time;

	steps = 0;
	transit_time = paths->path_len - 1;
	while (army)
	{
		mpath = min_path(paths);
		army->path = mpath->path;
		army->color.color = mpath->color.color;
		mpath->path == paths->path ? steps++ : 0;
		army = army->prev;
	}
	return (steps + transit_time);
}

void				renovate_listpath(t_listpath *listpath)
{
	while (listpath)
	{
		listpath->path_len = path_len(listpath->path);
		listpath = listpath->next;
	}
}
