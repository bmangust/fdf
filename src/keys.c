/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 20:20:58 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 21:06:58 by akraig           ###   ########.fr       */
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
		update_figure(SCALEZ, fdf, change_height);
	else if (key == MINUS || key == NUMMINUS)
		update_figure(SCALENZ, fdf, change_height);
	draw(fdf);
}

void	change_distance(int key, t_fdf *fdf)
{
	if (key == W_KEY)
		fdf->cam->distance += 0.1;
	else if (key == Q_KEY)
		fdf->cam->distance -= 0.1;
//	if (fdf->cam->distance < 1.4)
//		fdf->cam->distance = 1.4;
//	else if (fdf->cam->distance > 5)
//		fdf->cam->distance = 5;
	draw(fdf);
}

static void	projection_select(t_fdf *fdf)
{
	if (fdf->type_of_proj == TRUEISO)
		fdf->type_of_proj = ISO21;
	else if (fdf->type_of_proj == ISO21)
		fdf->type_of_proj = PERSPECTIVE;
	else if (fdf->type_of_proj == PERSPECTIVE)
		fdf->type_of_proj = TRUEISO;
	draw(fdf);
}

static int	key_press(int key, t_fdf *fdf)
{
	if (key == UP || key == DOWN || key == RIGHT ||
		key == LEFT || key == NUM2 || key == NUM8)
		move_select(key, fdf);
	else if (key == NUM1 || key == NUM3 || key == NUM4 ||
			key == NUM6 || key == NUM7 || key == NUM9)
		rotate_select(key, fdf);
	else if (key == PLUS || key == MINUS || key == NUMPLUS || key == NUMMINUS)
		scale_select(key, fdf);
	else if (key == P_KEY)
		projection_select(fdf);
	else if ((key == W_KEY || key == Q_KEY) && fdf->type_of_proj == PERSPECTIVE)
		change_distance(key, fdf);
	else if (key == R_KEY)
		update_figure(SCALENZ, fdf, reset_transform);
	else if (key == ESC)
		terminate(fdf);
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (fdf->mouse->is_pressed)
	{
		fdf->cam->anglex += (x - fdf->mouse->prev_x) * ROT_ANGLE / 10;
		fdf->cam->angley += (y - fdf->mouse->prev_y) * ROT_ANGLE / 10;
		draw(fdf);
	}
	fdf->mouse->prev_x = fdf->mouse->x;
	fdf->mouse->prev_y = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	return (0);
}

int	mouse_press(int key, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (key == WHUP || key == WHDN)
	{
		if (key == WHDN)
			update_figure(SHIFTNZ, fdf, shift_figure);
		else
			update_figure(SHIFTZ, fdf, shift_figure);
		draw(fdf);
	}
	else if (key == LMB)
		fdf->mouse->is_pressed = 1;
	return (0);
}

int	mouse_release(int key, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if (key == LMB)
		fdf->mouse->is_pressed = 0;
	return (0);
}


void 		key_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->window->win, 2, 0, key_press, fdf);
	//mlx_hook(fdf->window->win, 3, 0, key_release, fdf);
	mlx_hook(fdf->window->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->window->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->window->win, 6, 0, mouse_move, fdf);
	mlx_hook(fdf->window->win, CLOSE, 0, close_w, fdf);
}
