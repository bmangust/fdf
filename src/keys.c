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
	float m[3];

	m[0] = 1 / ROT_ANGLE;
	m[1] = 1 / ROT_ANGLE;
	m[2] = 1 / ROT_ANGLE;
	if (key == NUMPLUS)
		update_figure(SCALEZ, fdf, change_scale);
	else if (key == NUMMINUS)
		update_figure(SCALENZ, fdf, change_scale);
	else if (key == PLUS)
		update_figure(SCALEZ, fdf, change_height);
	else if (key == MINUS)
		update_figure(SCALENZ, fdf, change_height);
}

static void	projection_select(t_fdf *fdf)
{
	if (fdf->type_of_proj == TRUEISO)
		fdf->type_of_proj = ISO21;
	else if (fdf->type_of_proj == ISO21)
		fdf->type_of_proj = PERSPECTIVE;
	else if (fdf->type_of_proj == PERSPECTIVE)
		fdf->type_of_proj = TRUEISO;
}

int			key_press(int key, t_fdf *fdf)
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
	else if (key == NUM0 || key == NUM5)
		color_select(fdf, key);
	else if ((key == W_KEY || key == Q_KEY) && fdf->type_of_proj == PERSPECTIVE)
		change_distance(key, fdf);
	else if (key == R_KEY)
		update_figure(SCALENZ, fdf, reset_transform);
	else if (key == ESC)
		terminate(&fdf);
	draw(fdf);
	return (0);
}
