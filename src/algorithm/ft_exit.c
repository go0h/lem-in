/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:39:28 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/30 14:12:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		usage(void)
{
	ft_fprintf(2, "USAGE:\n");
	ft_fprintf(2, "\t%-4s - print decision without input map\n", "[-m]");
	ft_fprintf(2, "\t%-4s - turn on visualization\n", "[-v]");
	ft_fprintf(2, "\t%-4s - design map\n", "[-d]");
}

void			ft_exit(t_lem **lem, int err)
{
	ft_del_lem(lem);
	if (err == INVALID_INPUT)
		ft_fprintf(2, "Error: Invalid map\n");
	else if (err == START_END)
		ft_fprintf(2, "Error: Two starts/ends, or not start/end\n");
	else if (err == DOUBLE_VRX)
		ft_fprintf(2, "Error: Duplicate vertex or same coordinates\n");
	else if (err == ONE_COMPONENT)
		ft_fprintf(2, "Error: Start & end situated in different \
		connected components\n");
	else if (err == SDL_INIT_ERROR)
		ft_fprintf(2, "SDL could not initialize! SDL_Error: %s\n", \
		SDL_GetError());
	else if (err == SDL_WIN_ERROR)
		ft_fprintf(2, "SDL could not create a window! SDL_Error: %s\n", \
		SDL_GetError());
	else if (err == NORMAL_EXIT)
		exit(0);
	else if (err == USAGE)
		usage();
	else
		perror("Error: ");
	exit(err);
}
