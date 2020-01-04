/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:12:12 by astripeb          #+#    #+#             */
/*   Updated: 2019/09/16 18:54:30 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		dfs(t_lem *lem, t_vrx *vrx)
{
	t_adj *adj_t;

	if (vrx->visit)
		return (0);
	if (vrx->type == END)
		return (1);
	vrx->visit = 1;
	adj_t = vrx->adj;
	while (adj_t)
	{
		if (dfs(lem, adj_t->vrx))
			return (1);
		adj_t = adj_t->next;
	}
	return (0);
}
