/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:16:41 by akraig            #+#    #+#             */
/*   Updated: 2020/01/16 20:22:16 by akraig           ###   ########.fr       */
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
	mlx_string_put(mlx, win, 20, y += 20,
			0xFAFAFA, "NUM 1 - 3   rotate figure by X axes");
	mlx_string_put(mlx, win, 20, y += 20,
			0xFAFAFA, "NUM 4 - 6   rotate figure by Y axes");
	mlx_string_put(mlx, win, 20, y += 20,
			0xFAFAFA, "NUM 7 - 9   rotate figure by Z axes");
	mlx_string_put(mlx, win, 20, y += 20,
			0xFAFAFA, "P           change projection type");
	mlx_string_put(mlx, win, 20, y += 20,
			0xFAFAFA, "arrows      move figure");
}

void 	clear_img(void *img, int width, int height, t_fdf *fdf)
{
	char *addr;

	addr = mlx_get_data_addr(img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	ft_bzero(addr, width * height * fdf->bits_per_pixel / 8);
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

void	iso(t_dot *src, t_dot *dst, double proj_angle, t_fdf *fdf)
{
	dst->x = (int)round((src->x - src->y)
			* cos(proj_angle) * fdf->xyscale) + XBIAS;
	dst->y = (int)round(-src->z * fdf->zscale  + (src->x + src->y)
			* sin(proj_angle) * fdf->xyscale) + YBIAS;
}

int		project(t_fdf *fdf, double proj_angle,
		void(f)(t_dot*, t_dot*, double, t_fdf*))
{
	t_dot *src;
	t_dot *dst;

	src = fdf->transform->dot;
	dst = fdf->proj->dot;
	while (src)
	{
		f(src, dst, proj_angle, fdf);
		if (src->down)
		{
			f(src->down, dst->down, proj_angle, fdf);
			draw_line(*dst, *dst->down, fdf);
		}
		if (!(src->last))
		{
			f(src->next, dst->next, proj_angle, fdf);
			draw_line(*dst, *dst->next, fdf);
			src = src->next;
			dst = dst->next;
			continue ;
		}
		src = src->next->down;
		dst = dst->next->down;
	}
	return (OK);
}

static int		is_inside(t_dot dot) {
	if ((dot.x > 0) && (dot.x < IMAGE_WIDTH) &&
		(dot.y > 0) && (dot.y < IMAGE_HEIGHT))
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

int 	draw(t_fdf *fdf)
{
	if (!fdf)
		return (ERROR);
	clear_img(fdf->window->img, fdf->window->width, fdf->window->height, fdf);
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

void	draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf)
{
	int	delta[2];
	int	error;
	int sign[2];

	delta[0] = abs((int)(dot1.x - dot2.x));
	delta[1] = abs((int)(dot1.y - dot2.y));
	sign[0] = dot2.x < dot1.x ? 1 : -1;
	sign[1] = dot2.y < dot1.y ? 1 : -1;
	error = delta[0] - delta[1];
	while (dot2.x != dot1.x || dot2.y != dot1.y)
	{
		if (is_inside(dot2))
			pixel_put(fdf->window->img, dot2.x, dot2.y, fdf);
		if ((dot2.x - dot1.x) && (error * 2 > -delta[1]))
		{
			error -= delta[1];
			dot2.x += sign[0];
		}
		if ((dot2.y - dot1.y) && (error * 2 < delta[0]))
		{
			error += delta[0];
			dot2.y += sign[1];
		}
	}
}

//void	draw_line2(int x1, int y1, t_fdf *fdf)
//{
//	int	delta[2];
//	int	error;
//	int sign[2];
//
//	delta[0] = abs(x1 - fdf->coord->x);
//	delta[1] = abs(y1 - fdf->coord->y);
//	sign[0] = fdf->coord->x < x1 ? 1 : -1;
//	sign[1] = fdf->coord->y < y1 ? 1 : -1;
//	error = delta[0] - delta[1];
//	while (fdf->coord->x != x1 || fdf->coord->y != y1)
//	{
//		if (is_inside(fdf->coord))
//			pixel_put(fdf->window->img, fdf->coord->x, fdf->coord->y, fdf);
//		if ((fdf->coord->x - x1) && (error * 2 > -delta[1]))
//		{
//			error -= delta[1];
//			fdf->coord->x += sign[0];
//		}
//		if ((fdf->coord->y - y1) && (error * 2 < delta[0]))
//		{
//			error += delta[0];
//			fdf->coord->y += sign[1];
//		}
//	}
//}

//int		click_line(int button, int x, int y, t_fdf *fdf)
//{
//	(void)button;
//	if (fdf->window->clicked == 0)
//	{
//		fdf->coord->x = x;
//		fdf->coord->y = y;
//		fdf->window->clicked = 1;
//		mlx_pixel_put(fdf->window->mlx, fdf->window->win,
//					  fdf->coord->x, fdf->coord->y, fdf->window->color);
//	}
//	else
//	{
//		draw_line(x, y, fdf);
//		fdf->window->clicked = 0;
//		// printf("x: %d, y: %d\n", param->x, param->y);
//	}
//	return (0);
//}
