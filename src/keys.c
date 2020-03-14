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
	{
		update_figure(SHIFTZ, fdf, rotate);
		fdf->cam->az += ROT_ANGLE * SHIFTZ[2] * fdf->cam->rotation_speed;
	}
	else if (key == NUM7)
	{
		update_figure(SHIFTNZ, fdf, rotate);
		fdf->cam->az += ROT_ANGLE * SHIFTNZ[2] * fdf->cam->rotation_speed;
	}
	else if (key == NUM6)
	{
		update_figure(SHIFTY, fdf, rotate);
		fdf->cam->ay += ROT_ANGLE * SHIFTY[1] * fdf->cam->rotation_speed;
	}
	else if (key == NUM4)
	{
		update_figure(SHIFTNY, fdf, rotate);
		fdf->cam->ay += ROT_ANGLE * SHIFTNY[1] * fdf->cam->rotation_speed;
	}
	else if (key == NUM3)
	{
		update_figure(SHIFTX, fdf, rotate);
		fdf->cam->ax += ROT_ANGLE * SHIFTX[0] * fdf->cam->rotation_speed;
	}
	else if (key == NUM1)
	{
		update_figure(SHIFTNX, fdf, rotate);
		fdf->cam->ax += ROT_ANGLE * SHIFTNX[0] * fdf->cam->rotation_speed;
	}
	printf("ax: %f ay: %f az: %f\n\n", fdf->cam->ax, fdf->cam->ay, fdf->cam->az);
}

static void	scale_select(int key, t_fdf *fdf)
{
	if (key == NUMPLUS)
		update_figure(SCALEZ, fdf, change_scale);
	else if (key == NUMMINUS)
		update_figure(SCALENZ, fdf, change_scale);
	else if (key == PLUS)
	{
		printf("change_height_up\n");
		update_figure(NULL, fdf, change_height_up);
		update_figure(SCALEZ, fdf, update_rotatation);
		printf("\n");
	}
	else if (key == MINUS)
	{
		printf("change_height_down\n");
		update_figure(NULL, fdf, change_height_down);
		update_figure(SCALEZ, fdf, update_rotatation);
		printf("\n");
	}
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

void		print_map(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)fdf;
	(void)src;
	if (!shift)
		printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
	else if (shift[0])
		printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
	else if (shift[1])
		printf("% 6.3f % 6.3f % 6.3f\n", dst->x, dst->y, dst->z);
}

void		print_projected_map(t_fdf *fdf)
{
	t_dot *src;

	if (!fdf)
		return ;
	src = fdf->proj->dot;
	while (1)
	{
		printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
		src = src->next;
		if (src->last && src->down)
		{
			printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
			src = src->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
}

int			key_press(int key, t_fdf *fdf)
{
	if (key == LSHIFT || key == RSHIFT)
		fdf->cam->move_speed = 30;
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
		reset(NULL, fdf, reset_transform);
	else if (key == ESC)
		terminate(&fdf);
	else if (key == 6)
	{
		printf("map\n");
		update_figure(NULL, fdf, print_map);
		printf("\n");
	}
	else if (key == 7)
	{
		printf("transform\n");
		update_figure(SHIFTX, fdf, print_map);
		printf("\n");
	}
	else if (key == 8)
	{
		printf("rotate\n");
		update_figure(SHIFTY, fdf, print_map);
		printf("\n");
	}
	else if (key == 9)
	{
		printf("projected map\n");
		print_projected_map(fdf);
		printf("\n");
	}
	else if (key == 0)
		printf("ax: %f ay: %f az: %f\n\n", fdf->cam->ax, fdf->cam->ay, fdf->cam->az);
	draw(fdf);
	return (0);
}
