/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:35:59 by astripeb          #+#    #+#             */
/*   Updated: 2019/09/26 15:08:19 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		invalid_com(char *s)
{
	if (*s == '#' && ft_strcmp(s, "##start") && ft_strcmp(s, "##end"))
		return (1);
	return (0);
}

int		ft_validate_vrx(char **map)
{
	int i;

	if (ft_len_arr(map) != 3)
		return (0);
	if (map[0][0] == 'L' || ft_strchr(map[0], (int)'-'))
		return (0);
	i = 1;
	while (map[i])
	{
		if (!ft_isdigitstr(map[i]) ||\
			ft_int_len(ft_atoi(map[i])) != ft_strlen(map[i]))
			return (0);
		++i;
	}
	return (1);
}
