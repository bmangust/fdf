/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:20:49 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 14:33:18 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				delete_matrix(double **matrix)
{
	int i;

	i = -1;
	while (++i < 3)
		free(matrix[i]);
	free(matrix);
	matrix = NULL;
}

double		**create_matrix()
{
	double	**matrix;
	int		i[2];

	i[0] = -1;
	if (!(matrix = (double**)malloc(sizeof(double*) * 3)))
		return (NULL);
	while (++i[0] < 3)
	{
		if (!(matrix[i[0]] = (double*)malloc(sizeof(double) * 3)))
		{
			while (--i[0] >= 0)
				free(matrix[i[0]]);
			free(matrix);
			return (NULL);
		}
		i[1] = -1;
		while (++i[1] < 3)
			matrix[i[0]][i[1]] = 0;
	}
	return (matrix);
}

double				**rotation_x(double angle)
{
	double	**matrix;

	matrix = create_matrix();
	matrix[1][0] = cos(angle);
	matrix[1][2] = -sin(angle);
	matrix[2][1] = sin(angle);
	matrix[2][2] = cos(angle);
	matrix[0][0] = 1;
	return (matrix);
}

double				**rotation_y(double angle)
{
	double	**matrix;

	matrix = create_matrix();
	matrix[0][0] = cos(angle);
	matrix[0][2] = -sin(angle);
	matrix[2][0] = sin(angle);
	matrix[2][2] = cos(angle);
	matrix[1][1] = 1;
	return (matrix);
}

double				**rotation_z(double angle)
{
	double	**matrix;

	matrix = create_matrix();
	matrix[0][0] = cos(angle);
	matrix[0][1] = -sin(angle);
	matrix[1][0] = sin(angle);
	matrix[1][1] = cos(angle);
	matrix[2][2] = 1;
	return (matrix);
}

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
		attach_row(&(dest->dot), copy_row(tmp, map, dest));
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
