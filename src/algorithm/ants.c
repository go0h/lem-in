/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aks <aks@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:26:10 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/28 18:24:06 by aks              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		dissolve_army(t_ant **first_soldier)
{
	t_ant	*first;
	t_ant	*second;

	if (*first_soldier)
	{
		first = *first_soldier;
		while (first)
		{
			second = first;
			first = first->prev;
			free(second);
		}
		*first_soldier = NULL;
	}
}

void		first_soldier_commission(t_ant **army)
{
	t_ant	*old_soldier;

	if (*army)
	{
		old_soldier = *army;
		*army = old_soldier->next;
		*army ? (*army)->prev = NULL : 0;
		free(old_soldier);
	}
}

void		soldiers_commission(t_ant **army)
{
	t_ant	*first;
	t_ant	*second;
	t_ant	*temp;

	if (*army)
	{
		first = *army;
		while (first && first->path->vrx->type == END)
			first_soldier_commission(&first);
		*army = first;
		while (first)
		{
			if (first->path->vrx->type == END)
			{
				temp = first;
				first = first->next;
				first ? first->prev = NULL : 0;
				second->next = first;
				free(temp);
				continue ;
			}
			second = first;
			first = first->next;
		}
	}
}

t_ant		*new_soldier(int serial_number)
{
	t_ant	*soldier;

	if (!(soldier = (t_ant*)malloc(sizeof(t_ant))))
		return (NULL);
	soldier->serial_number = serial_number;
	soldier->path = NULL;
	soldier->next = NULL;
	soldier->prev = NULL;
	soldier->color.color = 0;
	return (soldier);
}

t_ant		*create_army(int number_of_soldiers)
{
	t_ant	*army;
	t_ant	*soldier;

	if (!(army = new_soldier(number_of_soldiers)))
		return (NULL);
	army ? army->next = NULL : 0;
	soldier = army;
	number_of_soldiers--;
	while (number_of_soldiers)
	{
		if (!(soldier->prev = new_soldier(number_of_soldiers)))
		{
			dissolve_army(&army);
			return (NULL);
		}
		soldier->prev->next = soldier;
		soldier = soldier->prev;
		number_of_soldiers--;
	}
	return (army);
}
