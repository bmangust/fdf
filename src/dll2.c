/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:18:22 by akraig            #+#    #+#             */
/*   Updated: 2020/03/08 17:18:23 by akraig           ###   ########.fr       */
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
			clear_map(&proj);
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
	int		i[2];

	tmp = map->dot;
	i[0] = 0;
	while (i[0] < map->height)
	{
		attach_row(&(dest->dot), copy_row(tmp, map, dest));
		tmp = tmp->down;
		i[0]++;
	}
	dest->width = map->width;
	dest->height = map->height;
}
