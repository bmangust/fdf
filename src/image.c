/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:16:41 by akraig            #+#    #+#             */
/*   Updated: 2019/11/24 16:35:17 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	iso(int *x, int *y, int z)
//{
//	int x_orig;
//	int y_orig;
//
//	x_orig = *x;
//	y_orig = *y;
//	*x = (x_orig - y_orig) * cos(0.523599);
//	*y = -z + (x_orig + y_orig) * sin(0.523599);
//}

/*
**	30°			0,523599		cos = 0,866025291583566		sin = 0,500000194337561
**	26.57°		0,46373398		cos = 0,894388561378677		sin = 0,447290846401959
*/

void	print_menu(t_fdf *fdf)
{
	void *mlx = fdf->window->mlx;
	void *win = fdf->window->win;
	int y;

	y = 10;
	mlx_string_put(mlx, win, 20, y, 0xFAFAFA, "controls");
	mlx_string_put(mlx, win, 20, y += 20, 0xFAFAFA, "NUM 1 and 3 rotate figure by X axes");
	mlx_string_put(mlx, win, 20, y += 20, 0xFAFAFA, "NUM 4 and 6 rotate figure by Y axes");
	mlx_string_put(mlx, win, 20, y += 20, 0xFAFAFA, "NUM 7 and 9 rotate figure by Z axes");
	mlx_string_put(mlx, win, 20, y += 20, 0xFAFAFA, "arrows move figure");
	mlx_string_put(mlx, win, 20, y += 20, 0xFAFAFA, "NUM 2 and 8 scale by Z axes");
}

void 	clear_img(void *img, int width, int height, t_fdf *fdf)
{
	char *addr;

	addr = mlx_get_data_addr(img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	ft_bzero(addr, width * height * fdf->bits_per_pixel / 8);
//	print_menu(fdf);
//	mlx_put_image_to_window(fdf->window->mlx, fdf->window->win, fdf->window->img, 0, 0);
}


int		draw(t_fdf *fdf)
{
	int x[2];
	int y[2];
	t_dot *tmp;

	if (!fdf)
		return (ERROR);
	clear_img(fdf->window->img, fdf->window->width, fdf->window->height, fdf);
	tmp = fdf->map->dot;
//	printf("==connect_dots==\n");
	while (tmp)
	{
//		printf("Current dot: %2d %2d %2d\n", tmp->x, tmp->y, tmp->z);
//		fdf->window->color = 0x00ffffff - (int)(tmp->z * 256 / 10);
		fdf->coord->x = (int)round((tmp->x - tmp->y) * cos(TRUEISO) * fdf->xyscale) + XBIAS;
		fdf->coord->y = (int)round(-tmp->z * fdf->zscale  + (tmp->x + tmp->y) * sin(TRUEISO) * fdf->xyscale) + YBIAS;
		x[0] = fdf->coord->x;
		y[0] = fdf->coord->y;
		if (tmp->down)
		{
			x[1] = (int)round((tmp->down->x - tmp->down->y) * cos(TRUEISO) * fdf->xyscale) + XBIAS;
			y[1] = (int)round(-tmp->down->z * fdf->zscale + (tmp->down->x + tmp->down->y) * sin(TRUEISO) * fdf->xyscale) + YBIAS;
//			printf("Line to: %2d %2d %2d, Line [(%d,%d), (%d,%d)]\n", tmp->down->x, tmp->down->y, tmp->down->z, fdf->coord->x, fdf->coord->y, x[1], y[1]);
			draw_line(x[1], y[1], fdf);
		}
		if (!(tmp->last))
		{
			fdf->coord->x = x[0];
			fdf->coord->y = y[0];
			x[1] = (int)round((tmp->next->x - tmp->next->y) * cos(TRUEISO) * fdf->xyscale) + XBIAS;
			y[1] = (int)round(-tmp->next->z * fdf->zscale  + (tmp->next->x + tmp->next->y) * sin(TRUEISO) * fdf->xyscale) + YBIAS;
//			printf("Line to: %2d %2d %2d, Line [(%d,%d), (%d,%d)]\n\n", tmp->next->x, tmp->next->y, tmp->next->z, fdf->coord->x, fdf->coord->y, x[1], y[1]);
			draw_line(x[1], y[1], fdf);
			tmp = tmp->next;
			continue ;
		}
		tmp = tmp->next->down;
	}
	mlx_put_image_to_window(fdf->window->mlx, fdf->window->win, fdf->window->img, 0, 0);
	print_menu(fdf);
	return (OK);
}

static int		is_inside(t_coord *coord) {
	if ((coord->x > 0) && (coord->x < coord->width) &&
		(coord->y > 0) && (coord->y < coord->height))
		return (1);
	return (0);
}

static void 	pixel_put(void *img, int x, int y, t_fdf *fdf)
{
	unsigned int i;
	char *addr;

	addr = mlx_get_data_addr(img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
	addr[i] = (char)fdf->window->color;				// B — Blue
	addr[++i] = (char)(fdf->window->color>>8);		// G — Green
	addr[++i] = (char)(fdf->window->color>>16);		// R — Red
	addr[++i] = 0;									// Alpha channel
}


void	draw_line(int x1, int y1, t_fdf *fdf)
{
	int	delta[2];
	int	error;
	int sign[2];

	delta[0] = abs(x1 - fdf->coord->x);
	delta[1] = abs(y1 - fdf->coord->y);
	sign[0] = fdf->coord->x < x1 ? 1 : -1;
	sign[1] = fdf->coord->y < y1 ? 1 : -1;
	error = delta[0] - delta[1];
	while (fdf->coord->x != x1 || fdf->coord->y != y1)
	{
		if (is_inside(fdf->coord))
			pixel_put(fdf->window->img, fdf->coord->x, fdf->coord->y, fdf);
		if ((fdf->coord->x - x1) && (error * 2 > -delta[1]))
		{
			error -= delta[1];
			fdf->coord->x += sign[0];
		}
		if ((fdf->coord->y - y1) && (error * 2 < delta[0]))
		{
			error += delta[0];
			fdf->coord->y += sign[1];
		}
	}
}

int		click_line(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	if (fdf->window->clicked == 0)
	{
		fdf->coord->x = x;
		fdf->coord->y = y;
		fdf->window->clicked = 1;
		mlx_pixel_put(fdf->window->mlx, fdf->window->win,
					  fdf->coord->x, fdf->coord->y, fdf->window->color);
	}
	else
	{
		draw_line(x, y, fdf);
		fdf->window->clicked = 0;
		// printf("x: %d, y: %d\n", param->x, param->y);
	}
	return (0);
}
