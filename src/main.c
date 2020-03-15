/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:31:08 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 15:27:21 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	void		*mlx;
	void		*win;
	void		*img;
	t_fdf		*fdf;
	t_map		*map;

	(void)ac;
	if ((mlx = mlx_init()) &&
		(win = mlx_new_window(mlx, IMAGE_WIDTH, IMAGE_HEIGHT, "mlx42")))
			img = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	else
		return (0);
	map = new_map();
	if (input(av[1], map) == ERROR)
	{
		mlx_destroy_image(mlx, img);
		return (0);
	}
	fdf = new_fdf(new_window(mlx, win, img), map);
	if (!fdf)
		terminate(&fdf);
	draw(fdf);
	key_hooks(fdf);
	mlx_loop(mlx);
	return (0);
}
