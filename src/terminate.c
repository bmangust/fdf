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

void	clear_dot(t_dot *dot)
{
	dot->down ? dot->down->up = NULL : 0;
	dot->prev ? dot->prev->next = NULL : 0;
	dot->next ? dot->next->prev = NULL : 0;
	dot->up ? dot->up->down = NULL : 0;
	dot->prev = NULL;
	dot->next = NULL;
	dot->down = NULL;
	dot->up = NULL;
	free(dot);
}

void	clear_map(t_map **map)
{
	t_dot	*tmp;
	t_dot	*next;
	t_dot	*row;

	row = (*map)->dot;
	while (row)
	{
		tmp = row->next;
		while (tmp != row)
		{
			next = tmp->next;
			clear_dot(tmp);
			tmp = NULL;
			tmp = next;
		}
		row = row->down;
		clear_dot(tmp);
		tmp = NULL;
	}
	free(*map);
	*map = NULL;
}

void	terminate(t_fdf **fdf)
{
	if (*fdf)
	{
		clear_map(&(*fdf)->map);
		clear_map(&(*fdf)->proj);
		clear_map(&(*fdf)->transform);
	}
	mlx_destroy_image((*fdf)->window->mlx, (*fdf)->window->img);
	mlx_destroy_window((*fdf)->window->mlx, (*fdf)->window->win);
	free((*fdf)->window);
	free((*fdf)->cam);
	free(*fdf);
	*fdf = NULL;
	exit(0);
}

int		close_w(void *param)
{
	terminate((t_fdf **)&param);
	exit(0);
}
