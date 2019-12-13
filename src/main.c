/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:31:08 by akraig            #+#    #+#             */
/*   Updated: 2019/12/13 21:08:39 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	void		*img;
	t_coord		*data;
	t_window	*window;
	t_fdf		*fdf;
	t_map		*map;
	(void)ac;

	width = 1500;
	height = 1500;
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "mlx42");
	img = mlx_new_image(mlx, width, height);
	data = new_coord(0, 0, height, width);
	window = new_window(mlx, win, img, width, height);
	map = new_map();
	input(av[1], map);
	fdf = new_fdf(window, data, map);
	draw(fdf);
	key_hooks(fdf);
	mlx_loop(mlx);
	return (0);
}
