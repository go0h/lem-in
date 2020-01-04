/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:54:09 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/23 22:35:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char		there_is_way(t_vrx *vrx_s, t_adj *adj_t, t_queue *queue)
{
	char		exist_out;

	exist_out = 0;
	if (vrx_s->sep)
	{
		if ((queue->weight > 0 && adj_t->weight < 0) || queue->weight < 0)
		{
			add_queue(&queue, adj_t->vrx, adj_t->weight);
			adj_t->vrx->anc = vrx_s;
			exist_out = 1;
		}
	}
	else
	{
		add_queue(&queue, adj_t->vrx, adj_t->weight);
		if (!adj_t->vrx->anc)
			adj_t->vrx->anc = vrx_s;
	}
	return (exist_out);
}

static int		bfs_algo(t_queue *queue)
{
	t_vrx		*vrx_s;
	t_adj		*adj_t;
	char		exist_out;

	while (queue)
	{
		vrx_s = queue->vrx;
		adj_t = vrx_s->adj;
		exist_out = 0;
		while (adj_t)
		{
			if (adj_t->dir)
			{
				if (!adj_t->vrx->visit)
					exist_out = there_is_way(vrx_s, adj_t, queue);
				if (adj_t->vrx->type == END &&\
				((vrx_s->sep && exist_out) || !vrx_s->sep))
					return (free_queue(&queue));
			}
			vrx_s->visit = exist_out || vrx_s->visit || !vrx_s->sep ? 1 : 0;
			adj_t = adj_t->next;
		}
		del_one_queue(&queue);
	}
	return (0);
}

static t_path	*shortest_path(t_vrx *vrx)
{
	t_path		*path;

	path = NULL;
	while (vrx && vrx->type != END)
		vrx = vrx->next;
	while (vrx->anc)
	{
		if (!add_path_to_begin(&path, vrx))
		{
			ft_free_one_path(&path);
			return (NULL);
		}
		vrx = vrx->anc;
	}
	if (!add_path_to_begin(&path, vrx))
	{
		ft_free_one_path(&path);
		return (NULL);
	}
	return (path);
}

void			clean_anc(t_vrx *vrx)
{
	while (vrx)
	{
		vrx->anc = NULL;
		vrx->visit = 0;
		vrx = vrx->next;
	}
}

t_path			*bfs(t_lem *lem)
{
	t_path		*path;
	t_queue		*queue;

	if (!(queue = new_queue(lem->vrx, 1)))
		return (NULL);
	lem->vrx->visit = 1;
	path = NULL;
	if (bfs_algo(queue))
		path = shortest_path(lem->vrx);
	clean_anc(lem->vrx);
	return (path);
}
