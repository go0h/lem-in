/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:32:16 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/25 13:58:20 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_free_adj(t_adj **adj_to_del)
{
	t_adj	*adj;
	t_adj	*temp;

	if (adj_to_del)
	{
		adj = *adj_to_del;
		while (adj)
		{
			temp = adj;
			adj = adj->next;
			temp->name ? free(temp->name) : 0;
			free(temp);
		}
		adj_to_del = NULL;
	}
}

static void		ft_free_vrxs(t_vrx **vrx_to_del)
{
	t_vrx		*vrx;
	t_vrx		*temp;

	if (vrx_to_del)
	{
		vrx = *vrx_to_del;
		while (vrx)
		{
			temp = vrx;
			ft_free_adj(&vrx->adj);
			free(vrx->name);
			vrx = vrx->next;
			free(temp);
		}
		vrx_to_del = NULL;
	}
}

void			ft_free_one_path(t_path **path_to_del)
{
	t_path	*path;
	t_path	*temp;

	if (path_to_del)
	{
		path = *path_to_del;
		while (path)
		{
			temp = path;
			path = path->next;
			free(temp);
		}
		*path_to_del = NULL;
	}
}

void			ft_free_path(t_listpath **listpath_to_del)
{
	t_listpath	*path;
	t_listpath	*temp;

	if (listpath_to_del)
	{
		path = *listpath_to_del;
		while (path)
		{
			temp = path;
			path = path->next;
			ft_free_one_path(&temp->path);
			free(temp);
		}
		*listpath_to_del = NULL;
	}
}

void			ft_del_lem(t_lem **lem_to_del)
{
	t_lem	*lem;

	if (lem_to_del)
	{
		lem = *lem_to_del;
		ft_free_vrxs(&lem->vrx);
		ft_free_path(&lem->listpath);
		ft_strdel(&lem->map);
		drop_visio(&lem->vis);
		free(lem);
		lem_to_del = NULL;
	}
}
