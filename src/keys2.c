/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:21:24 by akraig            #+#    #+#             */
/*   Updated: 2020/03/08 17:21:26 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_distance(int key, t_fdf *fdf)
{
	if (key == S_KEY)
		fdf->cam->distance += 0.1;
	else if (key == W_KEY)
		fdf->cam->distance -= 0.1;
	if (fdf->cam->distance < 1.1)
		fdf->cam->distance = 1.1;
	else if (fdf->cam->distance > 10)
		fdf->cam->distance = 10;
}

void	color_select(t_fdf *fdf, int key)
{
	if (key == NUM0)
		fdf->colorsceme = (fdf->colorsceme + 1) % 5;
	set_max_min_colors(fdf);
	change_color(fdf);
}

int			key_release(int key, t_fdf *fdf)
{
	if (key == LSHIFT || key == RSHIFT)
		fdf->cam->move_speed = 15;
	if (key == LCTRL || key == RCTRL)
		fdf->cam->rotation_speed = 2;
	draw(fdf);
	return (0);
}

void	key_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->window->win, 2, 0, key_press, fdf);
	mlx_hook(fdf->window->win, 3, 0, key_release, fdf);
	mlx_hook(fdf->window->win, CLOSE, 0, close_w, fdf);
}
