/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:03:27 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 20:29:53 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*add_last_dot(t_dot **head, t_dot *new)
{
	t_dot *tmp;

	if (head && new)
	{
		if (*head)
		{
			tmp = (*head)->prev;
			new->next = tmp->next;
			new->next->prev = new;
			new->prev = tmp;
			tmp->next = new;
			tmp->last = 0;
		}
		else
			*head = new;
		return (new);
	}
	return (NULL);
}

/*
**	i[0] - index in line
**	i[1] - x coord from begin
*/

t_dot	*create_row(char *line, t_map *map, int y)
{
	int		i[2];
	t_dot	*new;
	t_dot	*row;

	i[0] = 0;
	i[1] = 0;
	row = NULL;
	if (!line)
		return (NULL);
	while (line[i[0]])
	{
		if (!(new = new_dot(i[1] - map->width / 2,
				y - map->height / 2, ft_atoi(&line[i[0]]))))
			return (NULL);
		if (!map->max || (map->max && map->max->z < new->z))
			map->max = new;
		if (!map->min || (map->min && map->min->z > new->z))
			map->min = new;
		add_last_dot(&row, new);
		i[0] = find_next_number(line, i[0]);
		i[1]++;
	}
	return (row);
}

t_dot	*attach_row(t_dot **header, t_dot *row)
{
	t_dot	*temp_header;
	t_dot	*temp;

	if (!row || !header)
		return (NULL);
	if (!(*header))
	{
		*header = row;
		return (*header);
	}
	temp_header = *header;
	temp = row;
	while (1)
	{
		temp->up = temp_header->up;
		temp_header->up->down = temp;
		temp_header->up = temp;
		temp = temp->next;
		temp_header = temp_header->next;
		if (temp == row)
			break ;
	}
	return (*header);
}
