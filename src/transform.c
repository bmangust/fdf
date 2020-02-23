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

void	rotate(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[2];

	(void) src;
	if (shift[0])
	{
		fdf->cam->anglex = ROT_ANGLE * (shift[0] / STEP);
		i[0] = dst->y * cos(fdf->cam->anglex) + dst->z * sin(fdf->cam->anglex);
		dst->z = dst->z * cos(fdf->cam->anglex) - dst->y * sin(fdf->cam->anglex);
		dst->y = i[0];
	}
	else if (shift[1])
	{
		fdf->cam->angley = ROT_ANGLE * (shift[1] / STEP);
		i[0] = dst->x * cos(fdf->cam->angley) + dst->z * sin(fdf->cam->angley);
		dst->z = dst->z * cos(fdf->cam->angley) - dst->x * sin(fdf->cam->angley);
		dst->x = i[0];
	}
	else if (shift[2])
	{
		fdf->cam->anglez = ROT_ANGLE * (shift[2] / STEP);
		i[0] = dst->x * cos(fdf->cam->anglez) - dst->y * sin(fdf->cam->anglez);
		i[1] = dst->y * cos(fdf->cam->anglez) + dst->x * sin(fdf->cam->anglez);
		dst->x = i[0];
		dst->y = i[1];
	}
}

void	shift_figure(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void) fdf;
	(void) src;
	dst->x += shift[0];
	dst->y += shift[1];
	dst->z += shift[2] * 5;
}

void	change_scale(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void) fdf;
	(void) src;
	dst->x *= shift[2];
	dst->y *= shift[2];
	dst->z *= shift[2];
}

uint32_t	get_color(t_dot current, t_dot min, t_dot max)
{
	int		red;
	int		green;
	int		blue;
	double  percentage;

	percentage = percent(min.z, max.z, current.z);
	red = get_light((min.color >> 16) & 0xFF, (max.color >> 16) & 0xFF, percentage);
	green = get_light((min.color >> 8) & 0xFF, (max.color >> 8) & 0xFF, percentage);
	blue = get_light(min.color & 0xFF, max.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	change_color(uint32_t top_col, uint32_t bottom_col, t_fdf *fdf)
{
	t_dot *src;
	t_dot *dst;

	if (!fdf)
		return ;
	src = fdf->map->dot;
	dst = fdf->proj->dot;
	while (1)
	{
		dst->color = src->z == 0 ? bottom_col : top_col;
		src = src->next;
		dst = dst->next;
		if (src->last && src->down)
		{
			dst->color = src->z == 0 ? bottom_col : top_col;
			src = src->next->down;
			dst = dst->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	dst->color = src->z == 0 ? bottom_col : top_col;
	draw(fdf);
}

void	update_figure(float const *shift, t_fdf *fdf, void(*f)
		(float const*, t_dot*, t_dot*, t_fdf*))
{
	t_dot *src;
	t_dot *dst;

	if (!shift || !fdf)
		return ;
	src = fdf->map->dot;
	dst = fdf->transform->dot;
	while (1)
	{
		f(shift, src, dst, fdf);
		src = src->next;
		dst = dst->next;
		if (src->last && src->down)
		{
			f(shift, src, dst, fdf);
			src = src->next->down;
			dst = dst->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	f(shift, src, dst, fdf);
	draw(fdf);
}

void	reset_transform(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	(void) shift;
	(void) fdf;
}
