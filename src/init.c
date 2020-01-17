/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:36:05 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 19:54:06 by akraig           ###   ########.fr       */
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

t_mouse		*new_mouse()
{
	t_mouse *new;

	new = (t_mouse*)malloc(sizeof(t_mouse));
	if (!new)
		return (NULL);
	new->x = 0;
	new->y = 0;
	new->prev_x = 0;
	new->prev_y = 0;
	new->is_pressed = 0;
	return (new);
}

t_cam		*new_camera(void)
{
	t_cam *new;

	new = (t_cam*)malloc(sizeof(t_cam));
	if (!new)
		return (NULL);
	new->x = 0;
	new->y = 0;
	new->z = 0;
	new->distance = 2;
	new->anglex = 0;
	new->angley = 0;
	new->anglez = 0;
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
	new->clicked = 0;
	new->bits_per_pixel = 32;
	new->size_line = new->width * new->bits_per_pixel;
	new->endian = 0;
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
	new->mouse = new_mouse();
	new->cam = new_camera();
	copy_map(new->map, new->transform);
	copy_map(new->map, new->proj);
	if (!new->proj || !new->transform)
		return (NULL);
	new->coord = new_coord(0, 0);
	new->zscale = 1;
	new->xyscale = 40;
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
