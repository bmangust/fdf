/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:33:54 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 15:27:21 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	validate_line(char *line)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	while (line[++i])
		if ((line[i] >= '0' && line[i] <= '9') || ft_strchr(" -", line[i]))
		{
			if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
				cnt++;
			continue;
		}
		else
			return (ERROR);
	return (cnt);
}

/*
**	ret[0] - return from open
**	ret[1] - return from gnl
**	ret[2] - number of tokens in current line
*/

static int	count_map_params(char *file, t_map *map, char *line)
{
	int		ret[3];

	if ((ret[0] = open(file, O_RDONLY)) == -1)
		return (ERROR);
	while ((ret[1] = get_next_line(ret[0], &line)) > 0)
	{
		if (ret[1] == -1 || (ret[2] = validate_line(line)) == ERROR)
			return (ERROR);
		if (map->width == 0)
			map->width = ret[2];
		else if (map->width != ret[2])
		{
			ft_strdel(&line);
			return (ERROR);
		}
		++(map->height);
		ft_strdel(&line);
	}
	close(ret[0]);
	return (OK);
}

int			find_next_number(char *line, int i)
{
	int j;

	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			++i;
		while (line[i] && line[i] != ' ')
			++i;
		j = i;
		while (line[j] == ' ')
			++j;
		if (line[j] == '\0')
			return (j);
	}
	else
		while (line[i] && line[i] != ' ')
			++i;
	return (i);
}

/*
**	i[0] - file descriptor
**	i[1] - return from GNL
**	i[2] - index y in array
*/

int			get_coordinates(char *file, t_map *map, char *line)
{
	int		i[3];

	i[2] = 0;
	if ((i[0] = open(file, O_RDONLY)) == -1)
		return (ERROR);
	while ((i[1] = get_next_line(i[0], &line)) > 0)
	{
		if (!attach_row(&(map->dot), create_row(line, map, i[2])))
			return (ERROR);
		ft_strdel(&line);
		++i[2];
	}
	if (i[1] == -1)
		return (ERROR);
	close(i[0]);
	return (OK);
}

int			input(char *file, t_map *map)
{
	char	*line;

	line = NULL;
	if (count_map_params(file, map, line) == ERROR ||
		get_coordinates(file, map, line) == ERROR)
	{
		ft_strdel(&line);
		clear_map(&map);
		return (ERROR);
	}
	return (OK);
}
