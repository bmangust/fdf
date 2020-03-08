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

void	change_height(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)src;
	(void)dst;
	(void)fdf;
	src->z *= shift[2];
}

void	rotate(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[2];

	(void)src;
	if (shift[0])
	{
		fdf->cam->ax = ROT_ANGLE * (shift[0] / STEP);
		i[0] = dst->y * cos(fdf->cam->ax) + dst->z * sin(fdf->cam->ax);
		dst->z = dst->z * cos(fdf->cam->ax) - dst->y * sin(fdf->cam->ax);
		dst->y = i[0];
	}
	else if (shift[1])
	{
		fdf->cam->ay = ROT_ANGLE * (shift[1] / STEP);
		i[0] = dst->x * cos(fdf->cam->ay) + dst->z * sin(fdf->cam->ay);
		dst->z = dst->z * cos(fdf->cam->ay) - dst->x * sin(fdf->cam->ay);
		dst->x = i[0];
	}
	else if (shift[2])
	{
		fdf->cam->az = ROT_ANGLE * (shift[2] / STEP);
		i[0] = dst->x * cos(fdf->cam->az) - dst->y * sin(fdf->cam->az);
		i[1] = dst->y * cos(fdf->cam->az) + dst->x * sin(fdf->cam->az);
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

void	reset_transform(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	(void)shift;
	(void)fdf;
}
