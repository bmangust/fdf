/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:36:05 by akraig            #+#    #+#             */
/*   Updated: 2019/11/21 19:40:44 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

t_coord		*new_coord(int x, int y, int height, int width)
{
	t_coord *new;

	new = (t_coord*)malloc(sizeof(t_coord));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->width = width;
	new->height = height;
	return (new);
}

t_window	*new_window(void *mlx, void *win, void *img, int width, int height)
{
	t_window *new;

	if (!mlx || !win)	// || !img
		return (NULL);
	new = (t_window*)malloc(sizeof(t_window));
	if (!new)
		return (NULL);
	new->mlx = mlx;
	new->win = win;
	new->img = img;
	new->width = width;
	new->height = height;
	new->color = 0xFFFFFF;
	new->clicked = 0;
	return (new);
}

t_fdf	*new_fdf(t_window *window, t_coord *coord, t_map *map)
{
	t_fdf *new;

	new = (t_fdf*)malloc(sizeof(t_fdf));
	if (!new)
		return (NULL);
	new->window = window;
	new->map = map;
	new->coord = coord;
	new->zscale = 1;
	new->xyscale = 20;
	new->bits_per_pixel = 32;
	new->size_line = window->width * new->bits_per_pixel;
	new->endian = 0;
	return (new);
}

t_map		*new_map(void)
{
	t_map *new;

	new = (t_map*)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->width = 0;
	new->height = 0;
	new->min_z = 0;
	new->max_z = 0;
	new->dot = NULL;
	return (new);
}
