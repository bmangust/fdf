/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:45:22 by akraig            #+#    #+#             */
/*   Updated: 2020/03/08 16:45:27 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_max_min_colors(t_fdf *fdf)
{
	if (fdf->colorsceme == TEALORANGE)
	{
		fdf->map->max->color = GOLD;
		fdf->map->min->color = TEAL;
	}
	else if (fdf->colorsceme == BLACKWHITE)
	{
		fdf->map->max->color = WHITE;
		fdf->map->min->color = BLACK;
	}
	else if (fdf->colorsceme == PURPLEGOLD)
	{
		fdf->map->max->color = GOLD;
		fdf->map->min->color = PURPLE;
	}
	else if (fdf->colorsceme == SHADESBLUE)
	{
		fdf->map->max->color = LIGHTBLUE;
		fdf->map->min->color = BLUE;
	}
	else if (fdf->colorsceme == SINGLECOLOR)
	{
		fdf->map->max->color = fdf->color;
		fdf->map->min->color = fdf->color;
	}
}

void		change_color(t_fdf *fdf)
{
	t_dot *src;
	t_dot *dst;

	if (!fdf)
		return ;
	src = fdf->map->dot;
	dst = fdf->proj->dot;
	while (1)
	{
		dst->color = get_color(*src, *fdf->map->min, *fdf->map->max, NULL);
		src = src->next;
		dst = dst->next;
		if (src->last && src->down)
		{
			dst->color = get_color(*src, *fdf->map->min, *fdf->map->max, NULL);
			src = src->next->down;
			dst = dst->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	dst->color = get_color(*src, *fdf->map->min, *fdf->map->max, NULL);
	draw(fdf);
}

double		percent(double start, double end, double current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			get_light(double start, double end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

uint32_t	get_color(t_dot current, t_dot start, t_dot end, long *delta)
{
	int64_t	red;
	int64_t	green;
	int64_t	blue;
	double	percentage;

	if (current.color == start.color)
		return (current.color);
	if (!delta)
		percentage = percent(start.z, end.z, current.z);
	else if (delta[0] > delta[1])
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
					(end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF,
					(end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
