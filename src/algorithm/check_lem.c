/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:08:36 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/19 13:39:45 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			vrx_info(char *s)
{
	if (!ft_strcmp(s, "##start"))
		return (START);
	if (!ft_strcmp(s, "##end"))
		return (END);
	if (*s == '#')
		return (COMMENT);
	if (ft_char_count(s, '-') == 1)
		return (-1);
	return (0);
}

static void		first_start(t_lem *lem)
{
	t_vrx	*begin;
	t_vrx	*temp;
	t_vrx	*vrx;

	vrx = lem->vrx;
	if (vrx->type != 1)
	{
		begin = vrx;
		while (vrx->next && vrx->next->type != 1)
			vrx = vrx->next;
		temp = vrx->next;
		vrx->next = vrx->next->next;
		temp->next = begin;
		lem->vrx = temp;
	}
}

static int		check_start_end(t_vrx *vrx)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (vrx)
	{
		start += vrx->type == START ? 1 : 0;
		end += vrx->type == END ? 1 : 0;
		if (start == 2 || end == 2)
			return (0);
		vrx = vrx->next;
	}
	return (!start || !end ? 0 : 1);
}

static int		check_double_vertex(t_vrx *vrx)
{
	t_vrx	*cur;

	cur = vrx;
	while (cur->next)
	{
		vrx = cur->next;
		while (vrx)
		{
			if (!ft_strcmp(cur->name, vrx->name) ||\
				(cur->x == vrx->x && cur->y == vrx->y))
				return (0);
			vrx = vrx->next;
		}
		cur = cur->next;
	}
	return (1);
}

void			check_lem(t_lem *lem)
{
	if (!check_start_end(lem->vrx))
		ft_exit(&lem, START_END);
	first_start(lem);
	if (!check_double_vertex(lem->vrx))
		ft_exit(&lem, DOUBLE_VRX);
	if (!dfs(lem, lem->vrx))
		ft_exit(&lem, ONE_COMPONENT);
	unvisit(lem->vrx);
}
