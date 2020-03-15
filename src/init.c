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

t_dot		*new_dot(double x, double y, double z)
{
	t_dot *new;

	new = (t_dot*)malloc(sizeof(t_dot));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->show = 1;
	new->last = 1;
	new->color = new->z == 0 ? BLACK : WHITE;
	new->up = new;
	new->down = new;
	new->next = new;
	new->prev = new;
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
	new->distance = 2.2;
	new->rotation_speed = 2;
	new->move_speed = 15;
	new->ax = 0;
	new->ay = 0;
	new->az = 0;
	return (new);
}

t_window	*new_window(void *mlx, void *win, void *img)
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
	new->menu_height = MENU_HEIGHT;
	new->width = IMAGE_WIDTH;
	new->height = IMAGE_HEIGHT;
	new->bits_per_pixel = 32;
	new->size_line = new->width * new->bits_per_pixel;
	new->endian = 0;
	return (new);
}

t_fdf		*new_fdf(t_window *window, t_map *map)
{
	t_fdf *new;

	new = (t_fdf*)malloc(sizeof(t_fdf));
	if (!new)
		return (NULL);
	new->window = window;
	new->map = map;
	new->transform = new_map();
	new->rotate = new_map();
	new->proj = new_map();
	new->cam = new_camera();
	copy_map(new->map, new->transform);
	copy_map(new->map, new->rotate);
	copy_map(new->map, new->proj);
	if (!new->proj || !new->transform)
		return (NULL);
	new->zscale = 1;
	new->xyscale = 40;
	new->debug = 0;
	new->colorsceme = BLACKWHITE;
	new->color = TEAL;
	new->type_of_proj = TRUEISO;
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
	new->dot = NULL;
	new->max = NULL;
	new->min = NULL;
	return (new);
}
