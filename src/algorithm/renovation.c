/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renovation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:12:29 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/30 13:42:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		unvisit(t_vrx *vertex)
{
	while (vertex)
	{
		vertex->visit = 0;
		vertex = vertex->next;
	}
}

static int	check_rev_dir(t_vrx *vrx, char *edge)
{
	t_adj	*adj_t;

	if ((adj_t = get_adj(vrx->adj, edge)))
		return ((int)!adj_t->dir);
	return (0);
}

static void	renovate_rev_edge(t_vrx *vrx, char *edge)
{
	t_adj	*adj_t;

	if ((adj_t = get_adj(vrx->adj, edge)))
	{
		adj_t->dir = ON;
		adj_t->weight = 1;
	}
}

void		renovation_one_to_two_dir(t_lem *lem)
{
	t_vrx	*vrx_t;
	t_adj	*adj_t;

	vrx_t = lem->vrx;
	while (vrx_t)
	{
		vrx_t->sep = OFF;
		adj_t = vrx_t->adj;
		while (adj_t)
		{
			if (!adj_t->dir && check_rev_dir(adj_t->vrx, vrx_t->name))
				adj_t->weight = 0;
			else if (!adj_t->dir)
			{
				adj_t->dir = ON;
				adj_t->weight = 1;
				renovate_rev_edge(adj_t->vrx, vrx_t->name);
			}
			adj_t = adj_t->next;
		}
		vrx_t = vrx_t->next;
	}
}

void		full_renovation_lem(t_lem *lem)
{
	t_vrx	*vrx_t;
	t_adj	*adj_t;

	vrx_t = lem->vrx;
	while (vrx_t)
	{
		vrx_t->sep = OFF;
		vrx_t->visit = OFF;
		adj_t = vrx_t->adj;
		while (adj_t)
		{
			adj_t->dir = ON;
			adj_t->weight = 1;
			adj_t = adj_t->next;
		}
		vrx_t = vrx_t->next;
	}
}
