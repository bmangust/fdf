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
