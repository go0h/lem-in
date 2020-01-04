/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aks <aks@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:12:26 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/29 19:48:59 by aks              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		num_of_soldiers(t_ant *army)
{
	int i;

	i = 0;
	while (army)
	{
		army = army->next;
		++i;
	}
	return (i);
}

static char		*strjoinint(char *str, int n)
{
	char	*num;
	char	*join;

	if (!(num = ft_itoa(n)))
		return (NULL);
	if (!(join = ft_strjoin_s(str, num)))
	{
		free(num);
		return (NULL);
	}
	return(join);
}

void			draw_counters(t_lem *lem, t_ant *army, int meat)
{
	char		*str;
	t_color		c;
	SDL_Rect	rect;
	int			num;

	num = num_of_soldiers(army);
	c.color = ~0;
	if (!(str = strjoinint("Finish:  ", lem->ant_c - num)))
		ft_exit(&lem, MALLOC_FAILURE);
	lem->vis->texture = text2texture(lem->vis->render, lem->vis->font, str, c);
	rect = get_rectangle(100, 20, 10, 30);
	SDL_RenderCopy(lem->vis->render, lem->vis->texture, NULL, &rect);
	free(str);
	SDL_DestroyTexture(lem->vis->texture);
	if (!(str = strjoinint("Reserve: ", num - meat)))
		ft_exit(&lem, MALLOC_FAILURE);
	lem->vis->texture = text2texture(lem->vis->render, lem->vis->font, str, c);
	rect = get_rectangle(100, 20, 10, 10);
	SDL_RenderCopy(lem->vis->render, lem->vis->texture, NULL, &rect);
	free(str);
	SDL_DestroyTexture(lem->vis->texture);
	lem->vis->texture = NULL;
}
