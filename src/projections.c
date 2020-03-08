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

	(void)proj_angle;
	if (src->z <= fdf->cam->distance)
	{
		dest->show = 1;
		z = 4 / (fdf->cam->distance - src->z);
		if (fdf->cam->distance - src->z == INFINITY ||
			fdf->cam->distance - src->z == -INFINITY)
			z = DBL_MIN;
		dest->x = (int)(src->x * z * fdf->xyscale) + XBIAS;
		dest->y = (int)(src->y * z * fdf->xyscale) + YBIAS;
	}
	else
		dest->show = 0;
}

void		iso(t_dot *src, t_dot *dst, double proj_angle, t_fdf *fdf)
{
	dst->show = 1;
	dst->x = (int)((src->x - src->y) * cos(proj_angle) * fdf->xyscale) + XBIAS;
	dst->y = (int)(-src->z * fdf->zscale + (src->x + src->y)
							* sin(proj_angle) * fdf->xyscale) + YBIAS;
}

void		project(t_fdf *fdf, double proj_a,
				void (f)(t_dot*, t_dot*, double, t_fdf*))
{
	t_dot *src;
	t_dot *dst;

	src = fdf->transform->dot;
	dst = fdf->proj->dot;
	while (src)
	{
		f(src, dst, proj_a, fdf);
		if (src->down)
		{
			f(src->down, dst->down, proj_a, fdf);
			if ((is_inside(*dst) || is_inside(*dst->down)) && dst->show)
				draw_line(*dst, *dst->down, fdf);
		}
		if (!(src->last))
		{
			f(src->next, dst->next, proj_a, fdf);
			if ((is_inside(*dst) || is_inside(*dst->next)) && dst->show)
				draw_line(*dst, *dst->next, fdf);
			src = src->next;
			dst = dst->next;
			continue ;
		}
		src = src->next->down;
		dst = dst->next->down;
	}
}

void		update_figure(float const *shift, t_fdf *fdf,
		void (*f)(float const*, t_dot*, t_dot*, t_fdf*))
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
}
