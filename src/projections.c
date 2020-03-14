/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:11:13 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 20:11:18 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			is_inside(t_dot dot)
{
	if ((dot.x > 0) && (dot.x < IMAGE_WIDTH) &&
		(dot.y > 0) && (dot.y < IMAGE_HEIGHT))
		return (1);
	return (0);
}

void		project_perspective(t_dot *src, t_dot *dest,
								double proj_angle, t_fdf *fdf)
{
	double	z;
	t_dot 	*tmp;

	(void)proj_angle;
	if (src->z <= fdf->cam->distance)
	{
		tmp = new_dot(src->x, src->y, src->z);
		dest->show = 1;
		z = 4 / (fdf->cam->distance - tmp->z);
		if (fdf->cam->distance - tmp->z == INFINITY ||
			fdf->cam->distance - tmp->z == -INFINITY)
			z = DBL_MIN;
		dest->x = (int)(tmp->x * z * fdf->xyscale) + XBIAS + fdf->cam->x;
		dest->y = (int)(tmp->y * z * fdf->xyscale) + YBIAS + fdf->cam->y;
		free(tmp);
	}
	else
		dest->show = 0;
}

void		iso(t_dot *src, t_dot *dst, double proj_angle, t_fdf *fdf)
{
	t_dot 	*tmp;

	tmp = new_dot(src->x, src->y, src->z);
	dst->show = 1;
	dst->x = (int)((tmp->x - tmp->y) * cos(proj_angle) * fdf->xyscale)
					+ XBIAS + fdf->cam->x;
	dst->y = (int)(-tmp->z * fdf->zscale + (tmp->x + tmp->y)
					* sin(proj_angle) * fdf->xyscale) + YBIAS + fdf->cam->y;
	free(tmp);
}

void		project(t_fdf *fdf, double proj_angle,
				void (f)(t_dot*, t_dot*, double, t_fdf*))
{
	t_dot *d[2];

	d[0] = fdf->rotate->dot;
	d[1] = fdf->proj->dot;
	while (d[0])
	{
		f(d[0], d[1], proj_angle, fdf);
		if (d[0]->down)
		{
			f(d[0]->down, d[1]->down, proj_angle, fdf);
			if ((is_inside(*d[1]) || is_inside(*d[1]->down)) && d[1]->show)
				draw_line(*d[1], *d[1]->down, fdf);
		}
		if (!(d[0]->last))
		{
			f(d[0]->next, d[1]->next, proj_angle, fdf);
			if ((is_inside(*d[1]) || is_inside(*d[1]->next)) && d[1]->show)
				draw_line(*d[1], *d[1]->next, fdf);
			d[0] = d[0]->next;
			d[1] = d[1]->next;
			continue ;
		}
		d[0] = d[0]->next->down;
		d[1] = d[1]->next->down;
	}
}

void		update_figure(float const *shift, t_fdf *fdf,
		void (*f)(float const*, t_dot*, t_dot*, t_fdf*))
{
	t_dot *src;
	t_dot *dst;

	if (!fdf)
		return ;
//	dot[0] = shift ? fdf->map->dot : fdf->transform->dot;
//	dst = shift ? fdf->transform->dot : fdf->rotate->dot;
	src = shift ? fdf->transform->dot : fdf->map->dot;
	dst = shift ? fdf->rotate->dot : fdf->transform->dot;
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
}

void		reset_angles(t_fdf *fdf)
{
	fdf->cam->ax = 0;
	fdf->cam->ay = 0;
	fdf->cam->az = 0;
}

void		reset(float const *shift, t_fdf *fdf,
						  void (*f)(t_dot*, t_dot*, t_dot*, t_fdf*))
{
	t_dot *dot[3];

	if (!fdf)
		return ;
	dot[0] = fdf->map->dot;
	dot[1] = fdf->transform->dot;
	dot[2] = fdf->rotate->dot;
	while (1)
	{
		f(dot[0], dot[1], dot[2], fdf);
		dot[0] = dot[0]->next;
		dot[1] = dot[1]->next;
		dot[2] = dot[2]->next;
		if (dot[0]->last && dot[0]->down)
		{
			f(dot[0], dot[1], dot[2], fdf);
			dot[0] = dot[0]->next->down;
			dot[1] = dot[1]->next->down;
			dot[2] = dot[2]->next->down;
		}
		if (!(dot[0]->down) && dot[0]->last)
			break ;
	}
	f(dot[0], dot[1], dot[2], fdf);
	reset_angles(fdf);
}
