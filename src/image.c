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
				   LIGHTGRAY, "Q & W       change projection distance");
	mlx_string_put(mlx, win, 20, y += 20,
				   LIGHTGRAY, "            (in perspective)");
	mlx_string_put(mlx, win, 20, y += 20,
				   LIGHTGRAY, "arrows      move figure");
//	mlx_string_put(mlx, win, 520, y = 30,
//				   LIGHTGRAY, "arrows      move figure");
}

void 	clear_img(t_fdf *fdf)
{
	char *addr;
	void *img = fdf->window->img;
	int width = IMAGE_WIDTH;
	int height = IMAGE_HEIGHT;

	addr = mlx_get_data_addr(img, &(fdf->window->bits_per_pixel),
			&(fdf->window->size_line), &(fdf->window->endian));
	ft_bzero(addr, width * height * BITS_PER_PIXEL/ 8);
}

//int		project_iso(t_fdf *fdf, double proj_angle)
//{
//	int x[2];
//	int y[2];
//	t_dot *tmp;
//
//	tmp = fdf->proj->dot;
//	while (tmp)
//	{
//		fdf->coord->x = (int)round((tmp->x - tmp->y) * cos(proj_angle) * fdf->xyscale) + XBIAS;
//		fdf->coord->y = (int)round(-tmp->z * fdf->zscale  + (tmp->x + tmp->y) * sin(proj_angle) * fdf->xyscale) + YBIAS;
//		x[0] = fdf->coord->x;
//		y[0] = fdf->coord->y;
//		if (tmp->down)
//		{
//			x[1] = (int)round((tmp->down->x - tmp->down->y) * cos(proj_angle) * fdf->xyscale) + XBIAS;
//			y[1] = (int)round(-tmp->down->z * fdf->zscale + (tmp->down->x + tmp->down->y) * sin(proj_angle) * fdf->xyscale) + YBIAS;
//			draw_line(x[1], y[1], fdf);
//		}
//		if (!(tmp->last))
//		{
//			fdf->coord->x = x[0];
//			fdf->coord->y = y[0];
//			x[1] = (int)round((tmp->next->x - tmp->next->y) * cos(proj_angle) * fdf->xyscale) + XBIAS;
//			y[1] = (int)round(-tmp->next->z * fdf->zscale  + (tmp->next->x + tmp->next->y) * sin(proj_angle) * fdf->xyscale) + YBIAS;
//			draw_line(x[1], y[1], fdf);
//			tmp = tmp->next;
//			continue ;
//		}
//		tmp = tmp->next->down;
//	}
//	return (OK);
//}

static int		is_inside(t_dot dot) {
	if ((dot.x > 0) && (dot.x < IMAGE_WIDTH) &&
		(dot.y > 0) && (dot.y < IMAGE_HEIGHT))
		return (1);
	return (0);
}

void		project(t_fdf *fdf, double proj_a, void(f)(t_dot*, t_dot*, double, t_fdf*))
{
	t_dot *src;
	t_dot *dst;

	src = fdf->transform->dot;
	dst = fdf->proj->dot;
	while (src)
	{
		f(src, dst, proj_a, fdf);
		if (src->down)
		{
			f(src->down, dst->down, proj_a, fdf);
			if (is_inside(*dst) || is_inside(*dst->down))
				draw_line(*dst, *dst->down, fdf);
		}
		if (!(src->last))
		{
			f(src->next, dst->next, proj_a, fdf);
			if (is_inside(*dst) || is_inside(*dst->next))
				draw_line(*dst, *dst->next, fdf);
			src = src->next;
			dst = dst->next;
			continue ;
		}
		src = src->next->down;
		dst = dst->next->down;
	}
}

static void 	pixel_put(void *img, t_dot dot, t_fdf *fdf, unsigned int color)
{
	unsigned int i;
	char *addr;

	if (is_inside(dot) && dot.y > 180)
	{
		addr = mlx_get_data_addr(img, &(fdf->window->bits_per_pixel),
						&(fdf->window->size_line), &(fdf->window->endian));
		i = (dot.x * BITS_PER_PIXEL / 8) + (dot.y * fdf->window->size_line);
		addr[i] = (char)color;				// B — Blue
		addr[++i] = (char)(color>>8);		// G — Green
		addr[++i] = (char)(color>>16);		// R — Red
		addr[++i] = 0;						// Alpha channel
	}
}

int 	draw(t_fdf *fdf)
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
	mlx_put_image_to_window(fdf->window->mlx, fdf->window->win, fdf->window->img, 0, 0);
	print_menu(fdf);
	return (OK);
}

double percent(double start, double end, double current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(double start, double end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

unsigned int get_color(t_dot current, t_dot start, t_dot end, int *delta)
{
	int red;
	int green;
	int blue;
	double  percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta[0] > delta[1])
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf)
{
	int		delta[2];
	int		error;
	int		sign[2];
	t_dot	cur;

	delta[0] = abs((int)(dot1.x - dot2.x));
	delta[1] = abs((int)(dot1.y - dot2.y));
	sign[0] = dot2.x < dot1.x ? 1 : -1;
	sign[1] = dot2.y < dot1.y ? 1 : -1;
	error = delta[0] - delta[1];
	cur = dot1;
	while (dot2.x != cur.x || dot2.y != cur.y)
	{
		pixel_put(fdf->window->img, dot2, fdf, get_color(cur, dot1, dot2, delta));
		if ((dot2.x - cur.x) && (error * 2 > -delta[1]))
		{
			error -= delta[1];
			dot2.x += sign[0];
		}
		if ((dot2.y - cur.y) && (error * 2 < delta[0]))
		{
			error += delta[0];
			dot2.y += sign[1];
		}
	}
}
