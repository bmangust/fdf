/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 19:27:59 by akraig            #+#    #+#             */
/*   Updated: 2020/03/08 19:28:13 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		update_rotatation(float const *shift, t_dot *src,
							t_dot *dst, t_fdf *fdf)
{
	double	a;
	double	b;
	double	y;

	(void)shift;
	a = fdf->cam->ax;
	b = fdf->cam->ay;
	y = fdf->cam->az;
	dst->x = src->x * (cos(a) * cos(y) - sin(a) * cos(b) * sin(y)) -
			src->y * (sin(a) * cos(y) + cos(a) * cos(b) * sin(y)) +
			src->z * sin(b) * sin(y);
	dst->y = src->x * (cos(a) * sin(y) + sin(a) * cos(b) * cos(y)) -
			src->y * (sin(a) * sin(y) - cos(a) * cos(b) * cos(y)) -
			src->z * sin(b) * cos(y);
	dst->z = src->x * sin(a) * sin(b) + src->y * cos(a) * sin(b) +
			src->z * cos(b);
	if (fdf->debug)
		ft_printf("% 6.3f % 6.3f % 6.3f\n", dst->x, dst->y, dst->z);
}

void		reset_angles(t_fdf *fdf)
{
	fdf->cam->ax = 0;
	fdf->cam->ay = 0;
	fdf->cam->az = 0;
}

void		reset(t_fdf *fdf, void (*f)(t_dot*, t_dot*, t_dot*, t_fdf*))
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
