/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:16:41 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 19:19:41 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		print_menu(t_fdf *fdf, void *mlx, void *win)
{
	int y;

	y = 10;
	mlx_string_put(mlx, win, 380, y, 0xFAFAFA, "controls");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "NUM 1 - 3   rotate figure by X axes");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "NUM 4 - 6   rotate figure by Y axes");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "NUM 7 - 9   rotate figure by Z axes");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "P           change projection type");
	mlx_string_put(mlx, win, 20, y += 20,
					LIGHTGRAY, "arrows      move figure");
	y = 10;
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "NUM 0   change color scheme");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "NUM - / +   scale picture");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "R   reset transformations");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "Q & W       change projection distance");
	mlx_string_put(mlx, win, fdf->window->width / 2, y += 20,
					LIGHTGRAY, "            (in perspective)");
}

void		clear_img(t_fdf *fdf)
{
	char	*addr;
	void	*img;
	int		width;
	int		height;

	img = fdf->window->img;
	width = IMAGE_WIDTH;
	height = IMAGE_HEIGHT;
	addr = mlx_get_data_addr(img, &(fdf->window->bits_per_pixel),
			&(fdf->window->size_line), &(fdf->window->endian));
	ft_bzero(addr, width * height * BITS_PER_PIXEL / 8);
}

static void	pixel_put(void *img, t_dot dot, t_fdf *fdf, unsigned int color)
{
	unsigned int	i;
	char			*addr;

	if (is_inside(dot) && dot.y > MENU_HEIGHT)
	{
		addr = mlx_get_data_addr(img, &(fdf->window->bits_per_pixel),
						&(fdf->window->size_line), &(fdf->window->endian));
		i = (dot.x * BITS_PER_PIXEL / 8) + (dot.y * fdf->window->size_line);
		addr[i] = (char)color;
		addr[++i] = (char)(color >> 8);
		addr[++i] = (char)(color >> 16);
		addr[++i] = 0;
	}
}

int			draw(t_fdf *fdf)
{
	if (!fdf)
		return (ERROR);
	clear_img(fdf);
	if (fdf->type_of_proj == PERSPECTIVE)
		project(fdf, TRUEISO_ANGLE, project_perspective);
	else if (fdf->type_of_proj == TRUEISO)
		project(fdf, TRUEISO_ANGLE, iso);
	else if (fdf->type_of_proj == ISO21)
		project(fdf, ISO21_ANGLE, iso);
	mlx_put_image_to_window(fdf->window->mlx, fdf->window->win,
							fdf->window->img, 0, 0);
	print_menu(fdf, fdf->window->mlx, fdf->window->win);
	return (OK);
}

/*
**	delta[0], delta[1] - diff between x and y resp.
**	delta[2] error (delta[0] - delta[1])
*/

void		draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf)
{
	long	delta[3];
	int		sign[2];
	t_dot	cur;

	delta[0] = ft_absint((int)(dot1.x - dot2.x));
	delta[1] = ft_absint((int)(dot1.y - dot2.y));
	sign[0] = dot2.x < dot1.x ? 1 : -1;
	sign[1] = dot2.y < dot1.y ? 1 : -1;
	delta[2] = delta[0] - delta[1];
	cur = dot2;
	while ((dot1.x != cur.x || dot1.y != cur.y))
	{
		pixel_put(fdf->window->img, cur, fdf,
				get_color(cur, dot1, dot2, delta));
		if ((cur.x - dot1.x) && (delta[2] * 2 > -delta[1]))
		{
			delta[2] -= delta[1];
			cur.x += sign[0];
		}
		if ((cur.y - dot1.y) && (delta[2] * 2 < delta[0]))
		{
			delta[2] += delta[0];
			cur.y += sign[1];
		}
	}
}
