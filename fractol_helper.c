/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:49 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 10:02:28 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	clamp_mouse_location(t_prm *prm)
{
	if (prm->current_mouse_loc[X] > prm->win_size[X])
		prm->current_mouse_loc[X] = prm->win_size[X];
	if (prm->current_mouse_loc[X] < 0)
		prm->current_mouse_loc[X] = 0;
	if (prm->current_mouse_loc[Y] > prm->win_size[Y])
		prm->current_mouse_loc[Y] = prm->win_size[Y];
	if (prm->current_mouse_loc[Y] < 0)
		prm->current_mouse_loc[Y] = 0;
	prm->xside = (long double)prm->current_mouse_loc[X] / prm->win_size[X];
	prm->yside = (long double)prm->current_mouse_loc[Y] / prm->win_size[Y];
}

void	put_pixel_image_color(t_fractal *fractal, unsigned int color)
{
	t_prm	*prm;
	t_mlx	*mlx;
	int		loc;
	int		xy[2];

	prm = fractal->prm;
	mlx = prm->mlx;
	xy[X] = fractal->xyz[X];
	xy[Y] = fractal->xyz[Y];
	loc = (mlx->size_line / 4) * xy[Y];
	fractal->height = (long double)fractal->count / prm->iterations;
	fractal->image_size = loc + xy[X];
	if (xy[X] >= prm->win_size[X] || xy[Y] >= prm->win_size[Y])
		return ;
	if (xy[X] < 0 || xy[Y] < 0)
		return ;
	((unsigned int *)prm->mlx->image_add)[fractal->image_size] = color;
}

void	put_pixel_image(t_fractal *fractal, BOOL bblack)
{
	t_prm	*prm;
	t_mlx	*mlx;
	int		loc;
	int		xy[2];

	prm = fractal->prm;
	mlx = prm->mlx;
	xy[X] = fractal->xyz[X];
	xy[Y] = fractal->xyz[Y];
	loc = (mlx->size_line / 4) * xy[Y];
	fractal->height = (long double)fractal->count / prm->iterations;
	fractal->image_size = loc + xy[X];
	if (xy[X] >= prm->win_size[X] || xy[Y] >= prm->win_size[Y])
		return ;
	else if (xy[X] < 0 || xy[Y] < 0)
		return ;
	else if (bblack == TRUE)
		((unsigned int *)prm->mlx->image_add)[fractal->image_size] = \
		(int)(0 * INT_MAX) & (0xFFFFFF);
	else
		((unsigned int *)prm->mlx->image_add)[fractal->image_size] = \
		(int)(fractal->height * INT_MAX) & (0xFFFFFF);
}

void	fractal_settings(t_fractal *fractal, int (*ptr)(t_coords*), int index)
{
	t_prm	*prm;

	prm = fractal->prm;
	fractal->ptr = ptr;
	fractal->y = index * (prm->win_size[Y] / prm->cpucount);
	fractal->scale[X] = prm->decimal / (prm->win_size[X] + prm->scaleint);
	fractal->scale[Y] = prm->decimal / (prm->win_size[Y] + prm->scaleint);
	fractal->xyz[Y] = fractal->y;
	fractal->xyz[Z] = fractal->xyz[Y] + (prm->win_size[Y] / prm->cpucount);
	if (prm->bcommand == TRUE)
		clamp_mouse_location(prm);
	prm->cons[X] = -0.7 * (0.7885) * (prm->xside * (M_PI * 2));
	prm->cons[Y] = -0.7 * (0.7885) * (prm->yside * (M_PI * 2));
	prm->last_mouse_loc[X] = prm->current_mouse_loc[X];
	prm->last_mouse_loc[Y] = prm->current_mouse_loc[Y];
}

void	*base_fractal(void *ptr)
{
	t_fractal	*fract;
	t_prm		*prm;
	t_coords	coords;

	fract = (t_fractal *)ptr;
	prm = fract->prm;
	coords.prm = prm;
	while (fract->xyz[Y] < prm->win_size[Y] && fract->xyz[Y] < fract->xyz[Z])
	{
		fract->xyz[X] = 0;
		while (fract->xyz[X] < prm->win_size[X])
		{
			coords.cx = (fract->xyz[X] * fract->scale[X]) + prm->left;
			coords.cy = (fract->xyz[Y] * fract->scale[Y]) + prm->top;
			fract->count = (*fract->ptr)(&coords);
			if (fract->count != prm->iterations)
				put_pixel_image(fract, FALSE);
			else
				put_pixel_image(fract, TRUE);
			fract->xyz[X]++;
		}
		fract->xyz[Y]++;
	}
	return (NULL);
}
