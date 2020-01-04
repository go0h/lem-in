/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aks <aks@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:04:10 by astripeb          #+#    #+#             */
/*   Updated: 2019/10/29 18:32:42 by aks              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

SDL_Rect		get_rectangle(int width, int height, int x, int y)
{
	SDL_Rect		rectangle;

	rectangle.h = height;
	rectangle.w = width;
	rectangle.x = x;
	rectangle.y = y;
	return (rectangle);
}

SDL_Texture		*text2texture(SDL_Renderer *rend, TTF_Font *font,\
				char *str, t_color c)
{
	SDL_Color		color;
	SDL_Surface		*text_surface;
	SDL_Texture		*texture;

	color.a = c.t_rgb.alpha;
	color.b = c.t_rgb.blue;
	color.g = c.t_rgb.green;
	color.a = c.t_rgb.red;
	text_surface = TTF_RenderText_Solid(font, str, color);
	if (!text_surface)
		return (NULL);
	texture = SDL_CreateTextureFromSurface(rend, text_surface);
	if (!text_surface)
		return (NULL);
	SDL_FreeSurface(text_surface);
	return (texture);
}

void			texture2render(SDL_Renderer *rend, SDL_Texture *text,\
				SDL_Rect rect)
{
	SDL_RenderCopy(rend, text, NULL, &rect);
	SDL_RenderPresent(rend);
}