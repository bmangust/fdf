/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:11:13 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 20:38:22 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*copy_row(t_dot *row, t_map *map, t_map *proj)
{
	int		i;
	t_dot	*proj_row;
	t_dot	*new;

	i = 0;
	proj_row = NULL;
	while (i < map->width)
	{
		if (!(new = new_dot(row->x, row->y, row->z)))
		{
			clear_map(proj);
			return (NULL);
		}
		add_last_dot(&proj_row, new);
		row = row->next;
		i++;
	}
	return (proj_row);
}

void	copy_map(t_map *map, t_map *dest)
{
	t_dot	*tmp;
	int 	i[2];

	tmp = map->dot;
	i[0] = 0;
	while (i[0] < map->height)
	{
		attach_row(&(dest->dot),
				   copy_row(tmp, map, dest));
		tmp = tmp->down;
		i[0]++;
	}
	dest->width = map->width;
	dest->height = map->height;
	dest->min_z = map->min_z;
	dest->max_z = map->max_z;
}

void	matmul(double **matrix, t_dot *src, t_dot *dst)
{
	dst->x =
	src->x * matrix[0][0] + src->y * matrix[0][1] + src->z * matrix[0][2];
	dst->y =
	src->x * matrix[1][0] + src->y * matrix[1][1] + src->z * matrix[1][2];
	dst->z =
	src->x * matrix[2][0] + src->y * matrix[2][1] + src->z * matrix[2][2];
}

void	project_row(t_dot *row, t_map *map, double **m, t_dot *dst)
{
	int		i;

	i = 0;
	while (i < map->width)
	{
		matmul(m, row, dst);
		dst = dst->next;
		row = row->next;
		i++;
	}
}
void	transform(double **matrix, t_map *map, t_map *dest_map)
{
	t_dot	*src;
	t_dot	*dst;
	int 	i;

	src = map->dot;
	dst = dest_map->dot;
	i = 0;
	while (i < map->height)
	{
		project_row(src, map, matrix, dst);
		src = src->down;
		dst = dst->down;
		i++;
	}
}

void		project_perspective(t_dot *src, t_dot *dest, double proj_angle, t_fdf *fdf)
{
	double	r;
	(void) src;
	(void) proj_angle;

//	z = 1 / (fdf->distance - fdf->transform->dot->z);
	r = - 1 / fdf->distance;
	dest->x = (int)round(src->x / (1 + dest->z * r) * fdf->xyscale * 3) + XBIAS;
	dest->y = (int)round(src->y / (1 + dest->z * r) * fdf->xyscale * 3) + YBIAS;
}


//
//void	iso(t_dot *src, t_dot *dest, double proj_angle, t_fdf *fdf)
//{
//	dest->x = (int)round((src->x - src->y)
//						 * cos(proj_angle) * fdf->xyscale) + XBIAS;
//	dest->y = (int)round(-src->z * fdf->zscale  + (src->x + src->y)
//												  * sin(proj_angle) * fdf->xyscale) + YBIAS;
//}
//
//int		project(t_fdf *fdf, double proj_angle)
//{
//	t_dot *src;
//	t_dot *dst;
//
//	src = fdf->map->dot;
//	dst = fdf->proj->dot;
//	while (src)
//	{
//		iso(src, dst, proj_angle, fdf);
//		if (src->down)
//		{
//			iso(src, dst, proj_angle, fdf);
//			iso(src->down, dst->down, proj_angle, fdf);
//			draw_line(*dst, *dst->down, fdf);
//		}
//		if (!(src->last))
//		{
//			iso(src, dst, proj_angle, fdf);
//			iso(src->next, dst->next, proj_angle, fdf);
//			draw_line(*dst, *dst->next, fdf);
//			src = src->next;
//			dst = dst->next;
//			continue ;
//		}
//		src = src->next->down;
//	}
//	return (OK);
//}