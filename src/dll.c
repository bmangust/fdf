/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:03:27 by akraig            #+#    #+#             */
/*   Updated: 2019/11/21 19:29:19 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*new_dot(int x, int y, int z)
{
	t_dot *new;
	new = (t_dot*)malloc(sizeof(t_dot));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->last = 1;
	new->up = new;
	new->down = new;
	new->next = new;
	new->prev = new;
	return (new);
}

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
	int i[2];
	t_dot *new;
	t_dot *row;

	i[0] = 0;
	i[1] = 0;
	row = NULL;
	if (!line)
		return (NULL);
	while (line[i[0]])
	{
		if (!(new = new_dot(i[1], y, ft_atoi(&line[i[0]]))))
		{
			//delete row
			return (NULL);
		}
		if (map->max_z < new->z)
			map->max_z = new->z;
		if (map->min_z < new->z)
			map->min_z = new->z;
//		printf("(%2.2f,%2.2f, %2.2f) ", new->x, new->y, new->z);
		add_last_dot(&row, new);
		i[0] = find_next_number(line, i[0]);
		i[1]++;
	}
//	printf("\n");
	return (row);
}

void	attach_row(t_dot **header, t_dot *row)
{
	t_dot	*temp_header;
	t_dot	*temp;

	if (!row || !header)
		return ;
	if (!(*header))
	{
		*header = row;
		return ;
	}
	temp_header = *header;
	temp = row;
	while (1)
	{
		temp->up = temp_header->up;
		temp->down = NULL;
		temp_header->up->down = temp;
		temp_header->up = temp;
		temp = temp->next;
		temp_header = temp_header->next;
		if (temp == row)
			break ;
	}
}
