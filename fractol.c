/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:14:24 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:29:44 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	barnsley_location(t_fern *fern, t_fractal *fract)
{
	t_prm	*prm;

	prm = fract->prm;
	barnsley_fern_fractal(fern);
	fract->xyz[X] = fern->x[1] * prm->scaleint;
	fract->xyz[X] += prm->fern_xyz[X] + fern->spawn_xy[X];
	fract->xyz[Y] = fern->y[1] * prm->scaleint;
	fract->xyz[Y] += prm->fern_xyz[Y] + fern->spawn_xy[Y];
	fern->x[0] = fern->x[1];
	fern->y[0] = fern->y[1];
}

static void	*barnsley_fern(void *ptr)
{
	t_fractal		*fract;
	t_prm			*prm;
	t_fern			fern;
	int				iter;
	unsigned int	rgb[3];

	fract = (t_fractal *)ptr;
	prm = fract->prm;
	iter = prm->iterations;
	fern.spawn_xy[X] = prm->win_size[X] / 2;
	fern.spawn_xy[Y] = 10;
	while (iter > 0)
	{
		barnsley_location(&fern, fract);
		rgb[R] = ((fern.y[1] / 10.0) * 255);
		rgb[B] = 255 - rgb[R];
		put_pixel_image_color(fract, rgb[B] + (rgb[R] << 16));
		iter--;
	}
	return (NULL);
}

static void	create_thread(int (*ptr)(t_coords*), pthread_t *tid, t_prm *prm)
{
	int		rc;
	int		xy[2];
	BOOL	b_bzero;
	void	*ptr1;

	ptr1 = prm->fractal_ptr;
	if (ptr)
		rc = pthread_create(tid, NULL, base_fractal, ptr1);
	else
	{
		b_bzero = FALSE;
		if (prm->prev_loc[X] != prm->fern_xyz[X])
			b_bzero = TRUE;
		if (prm->prev_loc[Y] != prm->fern_xyz[Y])
			b_bzero = TRUE;
		if (prm->prev_loc[Z] != prm->scaleint || b_bzero == TRUE)
		{
			xy[X] = prm->win_size[X];
			xy[Y] = prm->win_size[Y];
			ft_bzero(prm->mlx->image_add, xy[X] * xy[Y] * sizeof(int));
		}
		rc = pthread_create(tid, NULL, barnsley_fern, ptr1);
	}
	if (rc)
		exit_program("error, unable to create thread", TRUE);
}

static void	multithreading_fractol(t_prm *prm, int (*ptr)(t_coords*))
{
	t_fractal	*fractal;
	int			index;
	pthread_t	*tid;

	tid = malloc(sizeof(pthread_t) * prm->cpucount);
	if (!tid)
		exit_program("error malloc failed", TRUE);
	fractal = malloc(sizeof(t_fractal) * prm->cpucount);
	if (!fractal)
		exit_program("error malloc failed", TRUE);
	index = 0;
	while (index < prm->cpucount)
	{
		fractal[index].prm = prm;
		fractal_settings(&fractal[index], ptr, index);
		prm->fractal_ptr = (void *)(&fractal[index]);
		create_thread(ptr, &tid[index], prm);
		index++;
	}
	index = 0;
	while (index < prm->cpucount)
		pthread_join(tid[index++], NULL);
	free(tid);
	free(fractal);
}

void	fractol(t_prm *prm)
{
	int			(*ptr)(t_coords*);
	int			mouse_loc[2];

	ptr = NULL;
	mlx_mouse_get_pos(prm->mlx->win_ptr, &mouse_loc[X], &mouse_loc[Y]);
	prm->current_mouse_loc[X] = mouse_loc[X];
	prm->current_mouse_loc[Y] = mouse_loc[Y];
	if (ft_strcmp(prm->fractol_name, "julia") == 0)
		ptr = julia_fractal;
	else if (ft_strcmp(prm->fractol_name, "mandelbrot") == 0)
		ptr = mandelbrot_fractal;
	else if (ft_strcmp(prm->fractol_name, "juliaset") == 0)
		ptr = juliaset_fractal;
	multithreading_fractol(prm, ptr);
	prm->prev_loc[X] = prm->fern_xyz[X];
	prm->prev_loc[Y] = prm->fern_xyz[Y];
	prm->prev_loc[Z] = prm->scaleint;
}
