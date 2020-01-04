/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:10:44 by pcredibl          #+#    #+#             */
/*   Updated: 2019/09/19 22:23:05 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_queue(t_queue **queue)
{
	t_queue		*first;
	t_queue		*second;

	if (queue)
	{
		first = *queue;
		while (first)
		{
			second = first;
			first = first->next;
			second->vrx = NULL;
			free(second);
		}
		*queue = NULL;
	}
	return (1);
}

void	del_one_queue(t_queue **queue)
{
	t_queue		*temp_q;

	if (queue && *queue)
	{
		temp_q = *queue;
		*queue = temp_q->next;
		temp_q->vrx = NULL;
		temp_q->next = NULL;
		free(temp_q);
	}
}

t_queue	*new_queue(t_vrx *vrx, char weight)
{
	t_queue		*new_q;

	if (!(new_q = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new_q->vrx = vrx;
	new_q->weight = weight;
	new_q->next = NULL;
	return (new_q);
}

void	add_queue(t_queue **queue, t_vrx *vrx, char weight)
{
	t_queue		*new_q;

	if (queue)
	{
		new_q = *queue;
		if (new_q)
		{
			while (new_q->next)
				new_q = new_q->next;
			if (!(new_q->next = new_queue(vrx, weight)))
				free_queue(queue);
		}
		else
		{
			if (!(*queue = new_queue(vrx, weight)))
				free_queue(queue);
		}
	}
}

t_vrx	*last_vrx_in_queue(t_queue *qu, t_vrx *vrx)
{
	t_vrx	*vrx_t;

	while (qu->next)
		qu = qu->next;
	vrx_t = get_vrx(vrx, qu->vrx->name);
	return (vrx_t);
}
