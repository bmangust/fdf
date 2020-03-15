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
		fdf->cam->y += SHIFTNY[1] * fdf->cam->move_speed;
	else if (key == DOWN)
		fdf->cam->y += SHIFTY[1] * fdf->cam->move_speed;
	else if (key == LEFT)
		fdf->cam->x += SHIFTNX[0] * fdf->cam->move_speed;
	else if (key == RIGHT)
		fdf->cam->x += SHIFTX[0] * fdf->cam->move_speed;
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
	rotate_update(key, fdf);
}

static void	scale_select(int key, t_fdf *fdf)
{
	if (key == NUMPLUS)
		update_figure(SCALEZ, fdf, change_scale);
	else if (key == NUMMINUS)
		update_figure(SCALENZ, fdf, change_scale);
	else if (key == PLUS)
	{
		if (fdf->debug)
			ft_printf("change_height_up\nax: %f ay: %f az: %f\n\n",
					fdf->cam->ax, fdf->cam->ay, fdf->cam->az);
		update_figure(NULL, fdf, change_height_up);
		update_figure(SCALEZ, fdf, update_rotatation);
		if (fdf->debug)
			ft_printf("\n");
	}
	else if (key == MINUS)
	{
		if (fdf->debug)
			ft_printf("change_height_down\nax: %f ay: %f az: %f\n\n",
					fdf->cam->ax, fdf->cam->ay, fdf->cam->az);
		update_figure(NULL, fdf, change_height_down);
		update_figure(SCALEZ, fdf, update_rotatation);
		if (fdf->debug)
			ft_printf("\n");
	}
}

static void	projection_select(t_fdf *fdf)
{
	if (fdf->type_of_proj == TRUEISO)
		fdf->type_of_proj = ISO21;
	else if (fdf->type_of_proj == ISO21)
		fdf->type_of_proj = PERSPECTIVE;
	else if (fdf->type_of_proj == PERSPECTIVE)
		fdf->type_of_proj = PERSPECTIVE;
}

int			key_press(int key, t_fdf *fdf)
{
	if (key == LSHIFT || key == RSHIFT)
		fdf->cam->move_speed = 80;
	else if (key == LCTRL || key == RCTRL)
		fdf->cam->rotation_speed = 4;
	else if (key == UP || key == DOWN || key == RIGHT ||
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
	else if ((key == W_KEY || key == S_KEY) && fdf->type_of_proj == PERSPECTIVE)
		change_distance(key, fdf);
	else if (key == R_KEY)
		reset(fdf, reset_transform);
	else if (key == ESC)
		terminate(&fdf);
	key_press2(key, fdf);
	draw(fdf);
	return (0);
}
