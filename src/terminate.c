/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:43:18 by akraig            #+#    #+#             */
/*   Updated: 2020/01/10 18:55:26 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    clear_map(t_map *map)
{
	t_dot	*tmp;
	t_dot	*next;
	t_dot	*row;

	tmp = map->dot;
	while (tmp)
	{
		row = tmp->down;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->down)
				tmp->down->up = NULL;
			if (tmp->prev)
				tmp->prev->next = NULL;
			if (tmp->next)
				tmp->next->prev = NULL;
			tmp->prev = NULL;
			tmp->next = NULL;
			tmp->down = NULL;
			free(tmp);
			tmp = next;
		}
		tmp = row;
	}
	free(map);
}

void        terminate(t_fdf *fdf)
{
	clear_map(fdf->map);
	clear_map(fdf->proj);
	clear_map(fdf->transform);
	fdf->map->dot = NULL;
	mlx_destroy_image(fdf->window->mlx, fdf->window->img);
	mlx_destroy_window(fdf->window->mlx, fdf->window->win);
	free(fdf->window);
	free(fdf->coord);
	free(fdf);
	exit(0);
}

int		        close_w(void *param)
{
	terminate(param);
	(void)param;
	exit(0);
}
