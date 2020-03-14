/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:33:24 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 19:54:06 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_height_up(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)src;
	(void)shift;
	(void)fdf;
	dst->z *= SCALEZ[2];
}

void	change_height_down(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)src;
	(void)shift;
	(void)fdf;
	dst->z *= SCALENZ[2];
}

void	update_rotatation(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	a;
	double	b;
	double	y;

	(void)shift;
	a = fdf->cam->ax;
	b = fdf->cam->ay;
	y = fdf->cam->az;
	//R
//	dst->x = src->x * (cos(a) * cos(y) - sin(a) * cos(b) * sin(y)) +
//			src->y * (cos(a) * sin(y) + sin(a) * cos(b) * cos(y)) +
//			src->z * sin(a) * sin(b);
//	dst->y = src->z * cos(a) * sin(b) -
//			src->x * (sin(a) * cos(y) + cos(a) * cos(b) * sin(y)) -
//			src->y * (sin(a) * sin(y) - cos(a) * cos(b) * cos(y));
//	dst->z = src->z * cos(b) +
//			src->x * sin(b) * sin(y) -
//			src->y * sin(b) * cos(y);

	//R'
	dst->x = src->x * (cos(a) * cos(y) - sin(a) * cos(b) * sin(y)) -
			src->y * (sin(a) * cos(y) + cos(a) * cos(b) * sin(y)) +
			src->z * sin(b) * sin(y);
	dst->y = src->x * (cos(a) * sin(y) + sin(a) * cos(b) * cos(y)) -
			src->y * (sin(a) * sin(y) - cos(a) * cos(b) * cos(y)) -
			src->z * sin(b) * cos(y);
	dst->z = src->x * sin(a) * sin(b) + src->y * cos(a) * sin(b) +
			src->z * cos(b);

//	rotate_z(NULL, src, dst, fdf);
//	rotate_x(NULL, dst, dst, fdf);
//	rotate_z(NULL, dst, dst, fdf);
	printf("% 6.3f % 6.3f % 6.3f\n", dst->x, dst->y, dst->z);
}

void	rotate(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[3];

	(void)src;
	if (shift[0])
	{
		i[2] = ROT_ANGLE * shift[0] * fdf->cam->rotation_speed;
		i[0] = dst->y * cos(i[2]) + dst->z * sin(i[2]);
		dst->z = dst->z * cos(i[2]) - dst->y * sin(i[2]);
		dst->y = i[0];
	}
	else if (shift[1])
	{
		i[2] = ROT_ANGLE * shift[1] * fdf->cam->rotation_speed;
		i[0] = dst->x * cos(i[2]) + dst->z * sin(i[2]);
		dst->z = dst->z * cos(i[2]) - dst->x * sin(i[2]);
		dst->x = i[0];
	}
	else if (shift[2])
	{
		i[2] = ROT_ANGLE * shift[2] * fdf->cam->rotation_speed;
		i[0] = dst->x * cos(i[2]) - dst->y * sin(i[2]);
		i[1] = dst->y * cos(i[2]) + dst->x * sin(i[2]);
		dst->x = i[0];
		dst->y = i[1];
	}
}

void	shift_figure(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)fdf;
	(void)src;
	dst->x += shift[0];
	dst->y += shift[1];
	dst->z += shift[2] * 5;
}

void	change_scale(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)fdf;
	(void)src;
	dst->x *= shift[2];
	dst->y *= shift[2];
	dst->z *= shift[2];
}

void	reset_transform(t_dot *src, t_dot *trf, t_dot *rot, t_fdf *fdf)
{
	(void)fdf;
	trf->x = src->x;
	trf->y = src->y;
	trf->z = src->z;
	rot->x = src->x;
	rot->y = src->y;
	rot->z = src->z;
}
