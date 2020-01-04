/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:58:29 by astripeb          #+#    #+#             */
/*   Updated: 2019/09/28 14:52:53 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	change_eds_wght(t_vrx *vrx_t, char *end, int weight)
{
	t_adj	*adj_t;

	adj_t = vrx_t->adj;
	while (adj_t)
	{
		if (!ft_strcmp(adj_t->name, end))
		{
			if (adj_t->weight == weight)
				adj_t = adj_t->next;
			else
			{
				adj_t->weight = weight;
				break ;
			}
		}
		else
			adj_t = adj_t->next;
	}
}

static void	separate_vrxs(t_path *path, char tumbler)
{
	path = path->next;
	while (path->next)
	{
		path->vrx->sep = tumbler;
		path = path->next;
	}
}

void		change_dir(t_vrx *vrx_t, char *end, char dir)
{
	t_adj	*adj_t;

	adj_t = vrx_t->adj;
	while (adj_t)
	{
		if (!ft_strcmp(adj_t->name, end))
		{
			if (adj_t->dir == dir)
				adj_t = adj_t->next;
			else
			{
				adj_t->dir = dir;
				break ;
			}
		}
		else
			adj_t = adj_t->next;
	}
}

void		redirect_lem(t_path *path, char tumb)
{
	t_path	*temp;

	temp = path;
	while (temp->next)
	{
		change_dir(temp->vrx, temp->next->vrx->name, tumb);
		change_eds_wght(temp->vrx, temp->next->vrx->name, !tumb ? 0 : 1);
		change_eds_wght(temp->next->vrx, temp->vrx->name, !tumb ? -1 : 1);
		temp = temp->next;
	}
	separate_vrxs(path, !tumb ? ON : OFF);
}

void		redir_lem(t_path *path)
{
	t_path	*temp;

	temp = path;
	while (temp->next)
	{
		change_dir(temp->vrx, temp->next->vrx->name, OFF);
		change_dir(temp->next->vrx, temp->vrx->name, OFF);
		temp = temp->next;
	}
}
