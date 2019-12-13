/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:33:24 by akraig            #+#    #+#             */
/*   Updated: 2019/12/13 20:20:07 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(int const *shift, t_dot *tmp)
{
	double	i;
	double	j;
	double	angle;

	if (shift[0])
	{
		angle = ROT_ANGLE * (shift[0] / STEP);
		i = tmp->y * cos(angle) + tmp->z * sin(angle);
		tmp->z = tmp->z * cos(angle) - tmp->y * sin(angle);
		tmp->y = i;
	}
	else if (shift[1])
	{
		angle = ROT_ANGLE * (shift[1] / STEP);
		i = tmp->x * cos(angle) + tmp->z * sin(angle);
		tmp->z = tmp->z * cos(angle) - tmp->x * sin(angle);
		tmp->x = i;
	}
	else if (shift[2])
	{
		angle = ROT_ANGLE * (shift[2] / STEP);
		i = tmp->x * cos(angle) - tmp->y * sin(angle);
		j = tmp->y * cos(angle) + tmp->x * sin(angle);
		tmp->x = i;
		tmp->y = j;
	}
}

void	shift_figure(int const *shift, t_dot *dot)
{
	dot->x += shift[0];
	dot->y += shift[1];
	dot->z += shift[2] * 5;
}

void	change_height(int const *shift, t_dot *dot)
{
	dot->z += shift[2];
}

void	update_figure(int const *shift, t_fdf *fdf, void(*f)(int const *shift, t_dot *dot))
{
	t_dot *tmp;

	if (!shift || !fdf)
		return ;
	tmp = fdf->map->dot;
	while (1)
	{
		f(shift, tmp);
//		printf("(%2.2f,%2.2f, %2.2f) ", tmp->x, tmp->y, tmp->z);
		tmp = tmp->next;
		if (tmp->last && tmp->down)
		{
			f(shift, tmp);
//			printf("(%2.2f,%2.2f, %2.2f)\n", tmp->x, tmp->y, tmp->z);
			tmp = tmp->next->down;
		}
		if (!(tmp->down) && tmp->last)
			break ;
	}
	f(shift, tmp);
	draw(fdf);
//	printf("(%2.2f,%2.2f, %2.2f)\n\n", tmp->x, tmp->y, tmp->z);
}
