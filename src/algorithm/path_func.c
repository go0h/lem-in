/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 11:10:27 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/29 21:19:27 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_path_color(t_listpath *lpath)
{
	int		i;

	i = 0;
	while (lpath)
	{
		i % 10 == 0 ? lpath->color.color = A_MAGENTA : 0;
		i % 11 == 1 ? lpath->color.color = A_DARKTURQUOISE : lpath->color.color;
		i % 11 == 2 ? lpath->color.color = A_YELLOW : lpath->color.color;
		i % 11 == 3 ? lpath->color.color = A_INDIANRED : lpath->color.color;
		i % 11 == 4 ? lpath->color.color = A_BLUE : lpath->color.color;
		i % 11 == 5 ? lpath->color.color = A_DARJKHAKI : lpath->color.color;
		i % 11 == 6 ? lpath->color.color = A_DARKORANGE : lpath->color.color;
		i % 11 == 7 ? lpath->color.color = A_CYAN : lpath->color.color;
		i % 11 == 8 ? lpath->color.color = A_LAWNREEN : lpath->color.color;
		i % 11 == 9 ? lpath->color.color = A_FIREBRICK : lpath->color.color;
		i % 11 == 10 ? lpath->color.color = A_MOCCASIN : lpath->color.color;
		lpath = lpath->next;
		i++;
	}
}

int			path_len(t_path *path)
{
	int		i;

	i = 0;
	while (path)
	{
		path = path->next;
		++i;
	}
	return (i - 1);
}

int			add_path_to_begin(t_path **begin, t_vrx *vrx)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (0);
	path->vrx = vrx;
	if (*begin)
		path->next = *begin;
	else
		path->next = NULL;
	*begin = path;
	return (1);
}

void		visit_listpath(t_listpath *listpath)
{
	t_path	*path;

	while (listpath)
	{
		path = listpath->path->next;
		while (path->next)
		{
			path->vrx->visit = 1;
			path = path->next;
		}
		listpath = listpath->next;
	}
}

int			count_paths(t_listpath *listpath)
{
	int	i;

	i = 0;
	while (listpath)
	{
		++i;
		listpath = listpath->next;
	}
	return (i);
}