/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 11:09:56 by pcredibl          #+#    #+#             */
/*   Updated: 2019/10/30 14:07:54 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vrx	*get_vrx(t_vrx *vrx, char *name)
{
	while (vrx && ft_strcmp(name, vrx->name))
		vrx = vrx->next;
	return (vrx);
}

t_adj	*get_adj(t_adj *adj, char *name)
{
	while (adj && ft_strcmp(name, adj->name))
		adj = adj->next;
	return (adj);
}

int		check_flags(char *flags, long int options)
{
	while (*flags && options)
	{
		if (*flags > 96 && *flags < 123)
		{
			if ((options >> (*flags - 71)) & 1)
				options ^= (1L << (*flags - 71));
		}
		else if (*flags > 64 && *flags < 91)
		{
			if ((options >> (*flags - 65)) & 1)
				options ^= (1L << (*flags - 65));
		}
		flags++;
	}
	return (options ? 0 : 1);
}

int		check_option(char *str, long int *options)
{
	int i;

	if (str[0] == '-')
	{
		i = 1;
		if (str[i] == 'h')
			return (1);
		while (str[i])
		{
			if (str[i] > 96 && str[i] < 123)
				*options |= (1L << (str[i] - 71));
			else if (str[i] > 64 && str[i] < 91)
			    *options |= (1L << (str[i] - 65));
			else
				return (-1);
			++i;
		}
	}
	return (0);
}

void	options(int ac, char **av, t_lem *lem)
{
	int			i;
	int			check;
	long int	options;

	options = 0;
	i = 0;
	while (i < ac)
	{
		check = check_option(av[i], &options);
		if (check == 1)
			ft_exit(&lem, USAGE);
		if (check == -1)
			ft_exit(&lem, INVALID_OPTION);
		++i;
	}
	if (!check_flags("mvd", options))
		ft_exit(&lem, USAGE);
	lem->visual = (options >> ('v' - 71)) & 1;
	lem->without_map = (options >> ('m' - 71)) & 1;
	lem->design_map = (options >> ('d' - 71)) & 1;
}
