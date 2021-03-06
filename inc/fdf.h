/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:43:18 by akraig            #+#    #+#             */
/*   Updated: 2020/01/17 19:54:06 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "mlx.h"

/*
**	RETURN STATUS
*/

# define ERROR -1
# define OK 1

/*
**	KEYS
*/

# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define NUM0 82
# define NUM1 83
# define NUM2 84
# define NUM3 85
# define NUM4 86
# define NUM5 87
# define NUM6 88
# define NUM7 89
# define NUM8 91
# define NUM9 92
# define ESC 53
# define P_KEY 35
# define R_KEY 15
# define W_KEY 13
# define S_KEY 1
# define CLOSE 17
# define LCTRL 256
# define LSHIFT 257
# define LCMND 259
# define RSHIFT 258
# define RCTRL 269
# define NUMPLUS 69
# define NUMMINUS 78
# define PLUS 24
# define MINUS 27

/*
**	GLOBAL CONSTANTS
*/

# define IMAGE_WIDTH 1000
# define IMAGE_HEIGHT 1000
# define XBIAS IMAGE_WIDTH / 2
# define YBIAS IMAGE_HEIGHT / 2
# define STEP 1
# define MENU_HEIGHT 160
# define SHIFTX (float[3]) {STEP, 0, 0}
# define SHIFTNX (float[3]) {-STEP, 0, 0}
# define SHIFTY (float[3]) {0, STEP, 0}
# define SHIFTNY (float[3]) {0, -STEP, 0}
# define SHIFTZ (float[3]) {0, 0, STEP}
# define SHIFTNZ (float[3]) {0, 0, -STEP}
# define SCALEZ (float[3]) {0, 0, 1.2}
# define SCALENZ (float[3]) {0, 0, 0.8}
# define TRUEISO_ANGLE 0.523599
# define ISO21_ANGLE 0.46373398
# define ROT_ANGLE 0.0872664626
# define BITS_PER_PIXEL 32
# define TRUEISO 1
# define ISO21 2
# define PERSPECTIVE 3

/*
**	COLORS
*/

# define TEAL 0x008080
# define GOLD 0xFFD700
# define PURPLE 0x900C3F
# define LIGHTBLUE 0x3B33C3
# define BLUE 0x2A248B
# define WHITE 0xFFFFFF
# define BLACK 0x101010
# define LIGHTGRAY 0xD3D3D3
# define BLACKWHITE 0
# define TEALORANGE 1
# define PURPLEGOLD 2
# define SHADESBLUE 3
# define SINGLECOLOR 4
# define NUMCOLORS 5

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	int				width;
	int				height;
	int				menu_height;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_window;

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int				last;
	int				show;
	unsigned int	color;
	struct s_dot	*up;
	struct s_dot	*down;
	struct s_dot	*next;
	struct s_dot	*prev;
}					t_dot;

typedef struct		s_cam
{
	double			x;
	double			y;
	double			z;
	double			ax;
	double			ay;
	double			az;
	double			distance;
	double			rotation_speed;
	double			move_speed;
}					t_cam;

typedef struct		s_map
{
	int				width;
	int				height;
	t_dot			*max;
	t_dot			*min;
	t_dot			*dot;
}					t_map;

typedef struct		s_fdf
{
	t_window		*window;
	t_map			*map;
	t_map			*transform;
	t_map			*rotate;
	t_map			*proj;
	t_cam			*cam;
	int				zscale;
	int				xyscale;
	int				colorsceme;
	int				color;
	int				debug;
	int				type_of_proj;
}					t_fdf;

int					input(char *file, t_map *map);
t_map				*new_map(void);
t_window			*new_window(void *mlx, void *win, void *img);
t_fdf				*new_fdf(t_window *window, t_map *map);
t_dot				*new_dot(double x, double y, double z);
t_dot				*add_last_dot(t_dot **head, t_dot *new);
t_dot				*create_row(char *line, t_map *map, int y);
t_dot				*attach_row(t_dot **header, t_dot *row);

void				key_hooks(t_fdf *fdf);
void				update_figure(float const *shift, t_fdf *fdf, void(*f)
						(float const *shift, t_dot *, t_dot*, t_fdf *fdf));
void				reset(t_fdf *fdf,
						void(*f)(t_dot *, t_dot *, t_dot*, t_fdf *fdf));
void				rotate(float const *shift, t_dot *dst,
								t_dot *src, t_fdf *fdf);
void				change_distance(int key, t_fdf *fdf);
void				color_select(t_fdf *fdf, int key);
int					key_press(int key, t_fdf *fdf);
void				key_press2(int key, t_fdf *fdf);
void				key_debug(int key, t_fdf *fdf);
void				change_scale(float const *shift, t_dot *dot,
								t_dot *dst, t_fdf *fdf);
void				reset_transform(t_dot *src, t_dot *trf,
								t_dot *rot, t_fdf *fdf);
void				change_height_up(float const *shift, t_dot *src,
								t_dot *dst, t_fdf *fdf);
void				change_height_down(float const *shift, t_dot *src,
								t_dot *dst, t_fdf *fdf);
void				change_color(t_fdf *fdf);
void				set_max_min_colors(t_fdf *fdf);
uint32_t			get_color(t_dot current, t_dot start, t_dot end,
								long *delta);

void				draw_line(t_dot dot1, t_dot dot2, t_fdf *fdf);
int					draw(t_fdf *fdf);
void				clear_img(t_fdf *fdf);
void				copy_map(t_map *map, t_map *dest);
int					find_next_number(char *line, int i);
int					get_coordinates(char *file, t_map *map, char *line);

void				clear_map(t_map **map);
void				terminate(t_fdf **fdf);
int					close_w(void *param);

void				project_perspective(t_dot *src, t_dot *dest,
								double proj_angle, t_fdf *fdf);
void				iso(t_dot *src, t_dot *dst, double proj_angle, t_fdf *fdf);
int					is_inside(t_dot dot);
void				project(t_fdf *fdf, double proj_a, void(f)(t_dot*, t_dot*,
								double, t_fdf*));
int					get_light(double start, double end, double percentage);
double				percent(double start, double end, double current);
void				update_rotatation(float const *shift, t_dot *src,
								t_dot *dst, t_fdf *fdf);
void				print_projected_map(t_fdf *fdf);
void				print_map(float const *shift, t_dot *src,
								t_dot *dst, t_fdf *fdf);
void				rotate_update(int key, t_fdf *fdf);
void				print_debug_menu(t_fdf *fdf, void *mlx, void *win);

#endif
