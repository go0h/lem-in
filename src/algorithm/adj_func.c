/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:48:05 by astripeb          #+#    #+#             */
/*   Updated: 2019/09/28 14:53:49 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_adj(t_lem *lem, char **v)
{
	int		i;
	int		n;
	t_vrx	*vrx;

	vrx = lem->vrx;
	if (!exist_vertex(vrx, v))
		ft_exit(&lem, INVALID_INPUT);
	i = 0;
	while (i < 2 && vrx)
	{
		if (!ft_strcmp(vrx->name, v[0]) || !ft_strcmp(vrx->name, v[1]))
		{
			i++;
			n = !ft_strcmp(vrx->name, v[0]) ? 1 : 0;
			if (!(vrx->adj = ft_addlst(vrx->adj, v[n], 1)))
				ft_exit(&lem, MALLOC_FAILURE);
		}
		vrx = vrx->next;
	}
	ft_free_arr(v);
	lem->edge_c += 1;
}

t_adj		*ft_addlst(t_adj *adj, char *elem, char weight)
{
	t_adj	*begin;

	if (adj)
	{
		begin = adj;
		while (adj->next)
			adj = adj->next;
		if (!(adj->next = (t_adj*)malloc(sizeof(t_adj))))
			return (NULL);
		adj = adj->next;
	}
	else
	{
		if (!(begin = (t_adj*)malloc(sizeof(t_adj))))
			return (NULL);
		adj = begin;
	}
	if (!(adj->name = ft_strdup(elem)))
		return (NULL);
	adj->next = NULL;
	adj->weight = weight;
	adj->vrx = NULL;
	adj->dir = ON;
	return (begin);
}

void		add_link_adj_to_vrx(t_lem *lem)
{
	t_adj *adj;
	t_vrx *vrx;

	vrx = lem->vrx;
	while (vrx)
	{
		adj = vrx->adj;
		while (adj)
		{
			adj->vrx = get_vrx(lem->vrx, adj->name);
			adj = adj->next;
		}
		vrx = vrx->next;
	}
}
