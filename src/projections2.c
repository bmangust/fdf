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

//void	rotate_x(double srcy, double srcz, t_dot *dst, t_fdf *fdf)
//{
//	double	i[2];
//
//	i[0] = srcy * cos(fdf->cam->ax) + srcz * sin(fdf->cam->ax);
//	dst->z = srcz * cos(fdf->cam->ax) - srcy * sin(fdf->cam->ax);
//	dst->y = i[0];
//}
//
//void	rotate_y(double srcx, double srcz, t_dot *dst, t_fdf *fdf)
//{
//	double	i[2];
//
//	i[0] = srcx * cos(fdf->cam->ay) + srcz * sin(fdf->cam->ay);
//	dst->z = srcz * cos(fdf->cam->ay) - srcx * sin(fdf->cam->ay);
//	dst->x = i[0];
//}
//
//void	rotate_z(double srcx, double srcy, t_dot *dst, t_fdf *fdf)
//{
//	double	i[2];
//
//	i[0] = srcx * cos(fdf->cam->az) - srcy * sin(fdf->cam->az);
//	i[1] = srcy * cos(fdf->cam->az) + srcx * sin(fdf->cam->az);
//	dst->x = i[0];
//	dst->y = i[1];
//}

void	rotate_x(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[2];

	(void)shift;
	if (!fdf->cam->ax)
		return ;
	i[0] = src->y * cos(fdf->cam->ax) + src->z * sin(fdf->cam->ax);
	dst->z = src->z * cos(fdf->cam->ax) - src->y * sin(fdf->cam->ax);
	dst->y = i[0];
}

void	rotate_y(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[2];

	(void)shift;
	if (!fdf->cam->ay)
		return ;
//	fdf->cam->ay += ROT_ANGLE * (shift[1] / STEP);
	i[0] = src->x * cos(fdf->cam->ay) + src->z * sin(fdf->cam->ay);
	dst->z = src->z * cos(fdf->cam->ay) - src->x * sin(fdf->cam->ay);
	dst->x = i[0];
}

void	rotate_z(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	double	i[2];

	(void)shift;
	if (!fdf->cam->az)
		return ;
//	fdf->cam->az += ROT_ANGLE * (shift[2] / STEP);
	i[0] = src->x * cos(fdf->cam->az) - src->y * sin(fdf->cam->az);
	i[1] = src->y * cos(fdf->cam->az) + src->x * sin(fdf->cam->az);
	dst->x = i[0];
	dst->y = i[1];
}

t_dot	project_dot(t_dot *src, t_dot *dst, t_fdf *fdf)
{
//	rotate_z(src->x, src->y, dst, fdf);
//	rotate_x(dst->y, dst->z, dst, fdf);
//	rotate_y(dst->x, dst->z, dst, fdf);
	rotate_z(NULL, src, dst, fdf);
	rotate_x(NULL, src, dst, fdf);
	rotate_y(NULL, src, dst, fdf);
	if (fdf->type_of_proj == PERSPECTIVE)
		project_perspective(dst, dst, 0, fdf);
	else if (fdf->type_of_proj == TRUEISO)
		iso(dst, dst, TRUEISO_ANGLE, fdf);
	else if (fdf->type_of_proj == ISO21)
		iso(dst, dst, ISO21_ANGLE, fdf);
	return (*dst);
}

void		project_one_by_one(t_fdf *fdf)
{
	t_dot *d[2];

	d[0] = fdf->transform->dot;
	d[1] = fdf->proj->dot;
	while (d[0])
	{
		if (d[0]->down)
		{
			draw_line(project_dot(d[0], d[1], fdf),
					project_dot(d[0]->down, d[1]->down, fdf), fdf);
		}
		if (!(d[0]->last))
		{
			draw_line(project_dot(d[0], d[1], fdf),
					  project_dot(d[0]->next, d[1]->next, fdf), fdf);
			d[0] = d[0]->next;
			d[1] = d[1]->next;
			continue ;
		}
		d[0] = d[0]->next->down;
		d[1] = d[1]->next->down;
	}
}
