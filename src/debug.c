/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 11:59:42 by akraig            #+#    #+#             */
/*   Updated: 2020/03/15 11:59:43 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_debug_menu(t_fdf *fdf, void *mlx, void *win)
{
	int y;

	y = 130;
	mlx_string_put(mlx, win, 20, y,
					LIGHTGRAY, "SHIFT   speeds up moving");
	mlx_string_put(mlx, win, fdf->window->width / 2, y,
					LIGHTGRAY, "CTRL   speeds up rotation");
	if (!fdf->debug)
		return ;
	mlx_string_put(mlx, win, 380, y += 20, 0xFAFAFA, "debug");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "LEFT COMMAND   enable debug output");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "print coordinates of maps:");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "Z             original");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "X             transformed");
	y = 150;
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 40,
					LIGHTGRAY, "C             rotated");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "V             projected");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "A             rotation angles");
}

void	rotate_update(int key, t_fdf *fdf)
{
	if (key == NUM9)
		fdf->cam->az += ROT_ANGLE * SHIFTZ[2] * fdf->cam->rotation_speed;
	else if (key == NUM7)
		fdf->cam->az += ROT_ANGLE * SHIFTNZ[2] * fdf->cam->rotation_speed;
	else if (key == NUM6)
		fdf->cam->ay += ROT_ANGLE * SHIFTY[1] * fdf->cam->rotation_speed;
	else if (key == NUM4)
		fdf->cam->ay += ROT_ANGLE * SHIFTNY[1] * fdf->cam->rotation_speed;
	else if (key == NUM3)
		fdf->cam->ax += ROT_ANGLE * SHIFTX[0] * fdf->cam->rotation_speed;
	else if (key == NUM1)
		fdf->cam->ax += ROT_ANGLE * SHIFTNX[0] * fdf->cam->rotation_speed;
}

void	print_map(float const *shift, t_dot *src, t_dot *dst, t_fdf *fdf)
{
	(void)fdf;
	(void)src;
	if (!shift)
		ft_printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
	else if (shift[0])
		ft_printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
	else if (shift[1])
		ft_printf("% 6.3f % 6.3f % 6.3f\n", dst->x, dst->y, dst->z);
}

void	print_projected_map(t_fdf *fdf)
{
	t_dot *src;

	if (!fdf)
		return ;
	src = fdf->proj->dot;
	while (1)
	{
		ft_printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
		src = src->next;
		if (src->last && src->down)
		{
			ft_printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
			src = src->next->down;
		}
		if (!(src->down) && src->last)
			break ;
	}
	ft_printf("% 6.3f % 6.3f % 6.3f\n", src->x, src->y, src->z);
}

void	key_debug(int key, t_fdf *fdf)
{
	if (key == 6)
	{
		ft_printf("map\n");
		update_figure(NULL, fdf, print_map);
		ft_printf("\n");
	}
	else if (key == 7)
	{
		ft_printf("transform\n");
		update_figure(SHIFTX, fdf, print_map);
		ft_printf("\n");
	}
	else if (key == 8)
	{
		ft_printf("rotate\n");
		update_figure(SHIFTY, fdf, print_map);
		ft_printf("\n");
	}
	else if (key == 9)
	{
		ft_printf("projected map\n");
		print_projected_map(fdf);
		ft_printf("\n");
	}
}
