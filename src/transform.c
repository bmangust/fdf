/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:33:24 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 20:15:12 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void) fdf;
	double	i;
	double	j;

	if (shift[0])
	{
		fdf->anglex = ROT_ANGLE * (shift[0] / STEP);
		i = dst->y * cos(fdf->anglex) + dst->z * sin(fdf->anglex);
		dst->z = dst->z * cos(fdf->anglex) - dst->y * sin(fdf->anglex);
		dst->y = i;
	}
	else if (shift[1])
	{
		fdf->angley = ROT_ANGLE * (shift[1] / STEP);
		i = dst->x * cos(fdf->angley) + dst->z * sin(fdf->angley);
		dst->z = dst->z * cos(fdf->angley) - dst->x * sin(fdf->angley);
		dst->x = i;
	}
	else if (shift[2])
	{
		fdf->anglez = ROT_ANGLE * (shift[2] / STEP);
		i = dst->x * cos(fdf->anglez) - dst->y * sin(fdf->anglez);
		j = dst->y * cos(fdf->anglez) + dst->x * sin(fdf->anglez);
		dst->x = i;
		dst->y = j;
	}
}

//void	rotate(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
//{
//	(void)	fdf;
//	int		i;
//
//	if (shift[0])
//	{
//		fdf->anglex += ROT_ANGLE * (shift[0] / STEP) / 20;
//		i = src->y * cos(fdf->anglex) + src->z * sin(fdf->anglex);
//		src->z = src->z * cos(fdf->anglex) - src->y * sin(fdf->anglex);
//		src->y = i;
//	}
//	else if (shift[1])
//	{
//		fdf->angley += ROT_ANGLE * (shift[1] / STEP) / 20;
//		dst->z = src->z * cos(fdf->angley) - src->x * sin(fdf->angley);
//		dst->x = src->x * cos(fdf->angley) + src->z * sin(fdf->angley);
//	}
//	else if (shift[2])
//	{
//		fdf->anglez += ROT_ANGLE * (shift[2] / STEP) / 20;
//		dst->x = src->x * cos(fdf->anglez) - src->y * sin(fdf->anglez);
//		dst->y = src->y * cos(fdf->anglez) + src->x * sin(fdf->anglez);
//	}
//}

void	shift_figure(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void) fdf;
	(void) src;
	dst->x += shift[0];
	dst->y += shift[1];
	dst->z += shift[2] * 5;
}

void	change_height(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void) fdf;
	(void) src;
	dst->z *= shift[2];
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
//		printf("(%2.2f,%2.2f, %2.2f) ", src->x, src->y, src->z);
		src = src->next;
		dst = dst->next;
		if (src->last && src->down)
		{
			f(shift, src, dst, fdf);
//			printf("(%2.2f,%2.2f, %2.2f)\n", src->x, src->y, src->z);
			src = src->next->down;
			dst = dst->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	f(shift, src, dst, fdf);
	draw(fdf);
//	printf("(%2.2f,%2.2f, %2.2f)\n\n", src->x, src->y, src->z);
}

void	reset_transform(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	(void) shift;
	(void) fdf;
}
