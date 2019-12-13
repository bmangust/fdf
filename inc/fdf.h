

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define ERROR -1
# define OK 1
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
# define CLOSE 17
# define LMB 1
# define RMB 2
# define MMB 3
# define WHUP 4
# define WHDN 5
# define WHDN 5
# define NUMPLUS 69
# define NUMMINUS 78
# define PLUS 24
# define MINUS 27
# define XBIAS 200
# define YBIAS 100
# define STEP 1
# define SHIFTX (int[3]) {STEP, 0, 0}
# define SHIFTNX (int[3]) {-STEP, 0, 0}
# define SHIFTY (int[3]) {0, STEP, 0}
# define SHIFTNY (int[3]) {0, -STEP, 0}
# define SHIFTZ (int[3]) {0, 0, STEP}
# define SHIFTNZ (int[3]) {0, 0, -STEP}
# define TRUEISO 0.523599
# define ISO21 0.46373398
# define ROT_ANGLE 0.0872664626	//5deg
//# define EDOM
//# define EILSEQ
//# define ERANGE
extern int			errno;

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	color;
	int				width;
	int				height;
	int				clicked;
}					t_window;

typedef struct		s_coord
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_coord;

typedef struct		s_dot
{
	double			x;
	double			y;
	double			z;
	int				last;
	struct s_dot	*up;
	struct s_dot	*down;
	struct s_dot	*next;
	struct s_dot	*prev;
}					t_dot;

typedef struct		s_map
{
	int				width;
	int				height;
	int				min_z;
	int				max_z;
	t_dot			*dot;
}					t_map;

typedef struct		s_fdf
{
	t_window		*window;
	t_coord			*coord;
	t_map			*map;
	int				zscale;
	int				xyscale;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_fdf;

int			input(char *file, t_map *map);
t_map		*new_map(void);
t_window	*new_window(void *mlx, void *win, void *img, int width, int height);
t_fdf		*new_fdf(t_window *window, t_coord *coord, t_map *map);
t_coord		*new_coord(int x, int y, int height, int width);
t_dot		*create_row(char *line, t_map *map, int y);
void		attach_row(t_dot **header, t_dot *row);

void 		key_hooks(t_fdf *fdf);
void		update_figure(int const *shift, t_fdf *fdf,
			void(*f)(int const *shift, t_dot *dot));
void		rotate(int const *shift, t_dot *tmp);
void		shift_figure(int const *shift, t_dot *dot);
void		change_height(int const *shift, t_dot *dot);
int			click_line(int button, int x, int y, t_fdf *fdf);
void		draw_line(int x1, int y1, t_fdf *fdf);
int			draw(t_fdf *fdf);
void 		clear_img(void *img, int width, int height, t_fdf *fdf);

int			find_next_number(char *line, int i);
int			get_coordinates(char *file, t_map *map, char *line);

void		initialize_coord(t_coord *new, int x, int y, int color);
void		terminate(t_fdf *fdf);
int			close_w(void *param);
#endif
