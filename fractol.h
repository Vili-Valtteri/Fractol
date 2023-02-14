/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:16:34 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:29:07 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define R 0
# define G 1
# define B 2
# define KEY_R 15
# define KEY_I 34
# define KEY_O 31
# define KEY_ESC 53
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE_BUTTON 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define BOOL int
# define TRUE 1
# define FALSE 0

# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "minilibx/mlx.h"
# include <pthread.h>

typedef struct s_prm
{
	struct s_mlx		*mlx;
	char				*fractol_name;
	int					win_size[3];
	int					scale[3];
	long double			scaleint;
	BOOL				bcommand;
	long double			decimal;
	int					mouse_loc[2];
	int					last_mouse_loc[2];
	int					current_mouse_loc[2];
	long double			fern_xyz[3];
	int					iterations;
	int					cpucount;
	long double			left;
	long double			top;
	long double			xside;
	long double			yside;
	long double			cons[2];
	long double			juliaset[2];
	long double			prev_loc[3];
	long double			temp_loc[2];
	unsigned int		color;
	int					seconds;
	void				*fractal_ptr;
}				t_prm;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
	int			size_line;
	int			erdian;
	int			bpp;
}				t_mlx;

typedef struct s_coords
{
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;
	t_prm		*prm;
}				t_coords;

typedef struct s_fractal
{
	t_prm		*prm;
	int			y;
	int			(*ptr)(t_coords*);
	long double	scale[2];
	int			count;
	long double	height;
	int			xyz[3];
	int			image_size;
}				t_fractal;

typedef struct s_fern
{
	long double	x[2];
	long double	y[2];
	int			spawn_xy[2];
	t_fractal	*fract;
}				t_fern;

void	exit_program(char *error_msg, BOOL berror);
void	handle_file(char *argv, int argc, t_prm *prm);
void	open_window(t_prm *prm);
int		keyboard_input(int key, void *ptr);
int		mlx_window_loop(void *ptr);
void	fractol(t_prm *prm);
int		mouse_input(int key, int x, int y, void *ptr);
int		mandelbrot_fractal(t_coords *coords);
int		julia_fractal(t_coords *coords);
int		juliaset_fractal(t_coords *coords);
void	barnsley_fern_fractal(t_fern *fern);
void	fractal_settings(t_fractal *fractal, int (*ptr)(t_coords*), int index);
void	put_pixel_image(t_fractal *fractal, BOOL bblack);
void	*base_fractal(void *ptr);
void	put_pixel_image_color(t_fractal *fractal, unsigned int color);

#endif
