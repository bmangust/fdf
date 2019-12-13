/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 20:20:58 by akraig            #+#    #+#             */
/*   Updated: 2019/12/13 21:08:39 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_select(int key, t_fdf *fdf)
{
	if (key == UP)
		update_figure(SHIFTNY, fdf, shift_figure);
	else if (key == DOWN)
		update_figure(SHIFTY, fdf, shift_figure);
	else if (key == LEFT)
		update_figure(SHIFTNX, fdf, shift_figure);
	else if (key == RIGHT)
		update_figure(SHIFTX, fdf, shift_figure);
	else if (key == NUM2)
		update_figure(SHIFTNZ, fdf, shift_figure);
	else if (key == NUM8)
		update_figure(SHIFTZ, fdf, shift_figure);
}

static void	rotate_select(int key, t_fdf *fdf)
{
	if (key == NUM9)
		update_figure(SHIFTZ, fdf, rotate);
	else if (key == NUM7)
		update_figure(SHIFTNZ, fdf, rotate);
	else if (key == NUM6)
		update_figure(SHIFTY, fdf, rotate);
	else if (key == NUM4)
		update_figure(SHIFTNY, fdf, rotate);
	else if (key == NUM3)
		update_figure(SHIFTX, fdf, rotate);
	else if (key == NUM1)
		update_figure(SHIFTNX, fdf, rotate);
}

static void	scale_select(int key, t_fdf *fdf)
{
	if (key == PLUS || key == NUMPLUS)
		update_figure(SHIFTZ, fdf, change_height);
	else if (key == MINUS || key == NUMMINUS)
		update_figure(SHIFTNZ, fdf, change_height);
}

static int	key_press(int key, t_fdf *fdf)
{
	if (key == UP || key == DOWN || key == RIGHT || key == LEFT ||
		key == NUM2 || key == NUM8)
		move_select(key, fdf);
	else if (key == NUM1 || key == NUM3 || key == NUM4 || key == NUM6 ||
			 key == NUM7 || key == NUM9)
		rotate_select(key, fdf);
	else if (key == PLUS || key == MINUS || key == NUMPLUS || key == NUMMINUS)
		scale_select(key, fdf);
	else if (key == ESC)
		terminate(fdf);
	return (0);
}

void 		key_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->window->win, 2, 0, key_press, fdf);
	mlx_hook(fdf->window->win, 4, 0, key_press, fdf);
	//mlx_hook(fdf->window->win, 3, 0, key_release, fdf);
	mlx_hook(fdf->window->win, CLOSE, 0, close_w, fdf);
}
