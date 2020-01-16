/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:36:05 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 17:29:27 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

t_coord		*new_coord(int x, int y)
{
	t_coord *new;

	new = (t_coord*)malloc(sizeof(t_coord));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	return (new);
}

t_window	*new_window(void *mlx, void *win, void *img, int width, int height)
{
	t_window *new;

	if (!mlx || !win)
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

t_fdf	*new_fdf(t_window *window, t_map *map)
{
	t_fdf *new;

	new = (t_fdf*)malloc(sizeof(t_fdf));
	if (!new)
		return (NULL);
	new->window = window;
	new->map = map;
	new->transform = new_map();
	new->proj = new_map();
	copy_map(new->map, new->transform);
	copy_map(new->map, new->proj);
	if (!new->proj || !new->transform)
		return (NULL);
	new->coord = new_coord(0, 0);
	new->anglex = 0;
	new->angley = 0;
	new->anglez = 0;
	new->zscale = 1;
	new->xyscale = 20;
	new->bits_per_pixel = 32;
	new->size_line = window->width * new->bits_per_pixel;
	new->endian = 0;
	new->distance = 2;
	new->type_of_proj = ISO21;
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
	new->coords = NULL;
	new->dot = NULL;
	return (new);
}
