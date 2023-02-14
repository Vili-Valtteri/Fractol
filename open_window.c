/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:45:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/14 11:14:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	default_fractal_settings(t_prm *prm)
{
	long double	left;
	long double	top;

	prm->cpucount = sysconf(_SC_NPROCESSORS_ONLN);
	prm->bcommand = FALSE;
	prm->scaleint = 100;
	prm->xside = 1.0;
	prm->yside = prm->xside;
	prm->decimal = 5.0;
	prm->iterations = 50;
	left = prm->decimal + (prm->decimal / ((prm->win_size[X]) + prm->scaleint));
	left = left / ((prm->win_size[X]) + prm->scaleint) * (prm->win_size[X] / 2);
	top = prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint));
	top = top / (prm->win_size[Y] + prm->scaleint) * (prm->win_size[Y] / 2);
	prm->left = 0.0;
	prm->top = 0.0;
	prm->left -= left;
	prm->top -= top;
	ft_bzero(prm->fern_xyz, sizeof(prm->fern_xyz));
	prm->fern_xyz[Z] = 1.0;
}

static void	default_window_settings(t_prm *prm)
{
	prm->win_size[X] = 1792;
	prm->win_size[Y] = 1280;
	ft_bzero(&prm->scale, sizeof(prm->scale));
}

void	open_window(t_prm *prm)
{
	t_mlx	*mlx;
	int		xy[2];

	default_window_settings(prm);
	default_fractal_settings(prm);
	xy[X] = prm->win_size[X];
	xy[Y] = prm->win_size[Y];
	mlx = prm->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, xy[X], xy[Y], "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, xy[X], xy[Y]);
	mlx->image_add = \
	mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->size_line, &mlx->erdian);
	mlx_loop_hook(mlx->mlx_ptr, mlx_window_loop, prm);
	mlx_key_hook(mlx->win_ptr, keyboard_input, prm);
	mlx_mouse_hook(mlx->win_ptr, mouse_input, prm);
	mlx_loop(mlx->mlx_ptr);
}
