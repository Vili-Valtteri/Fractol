/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:43:36 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:01:30 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_fractal(t_coords *coords)
{
	int			count;
	long double	tempx;
	long double	cond;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	cond = coords->zx * coords->zx + coords->zy * coords->zy;
	while ((cond < 4) && (count < coords->prm->iterations))
	{
		tempx = coords->zx * coords->zx - coords->zy * coords->zy + coords->cx;
		coords->zy = (2 * coords->zx * coords->zy) + coords->cy;
		coords->zx = tempx;
		count++;
		cond = coords->zx * coords->zx + coords->zy * coords->zy;
	}
	return (count);
}

int	julia_fractal(t_coords *coords)
{
	int			count;
	long double	tempx;
	long double	cond;
	long double	zx2;
	t_prm		*prm;

	prm = coords->prm;
	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	cond = coords->zx * coords->zx + coords->zy * coords->zy;
	while ((cond < 4) && (count < coords->prm->iterations))
	{
		zx2 = coords->zx * coords->zx;
		tempx = zx2 - coords->zy * coords->zy + prm->cons[X];
		coords->zy = 2 * coords->zx * coords->zy + prm->cons[Y];
		coords->zx = tempx;
		count++;
		cond = coords->zx * coords->zx + coords->zy * coords->zy;
	}
	return (count);
}

int	juliaset_fractal(t_coords *coords)
{
	int		count;
	double	consx;
	double	consy;

	count = 0;
	consx = coords->prm->juliaset[X];
	consy = coords->prm->juliaset[Y];
	while (count < coords->prm->iterations)
	{
		coords->zx = coords->cx;
		coords->zy = coords->cy;
		coords->cx = coords->zx * coords->zx - coords->zy * coords->zy + consx;
		coords->cy = 2 * coords->zx * coords->zy + consy;
		if ((coords->cx * coords->cx + coords->cy * coords->cy) > 4)
			break ;
		count++;
	}
	return (count);
}

void	barnsley_fern_fractal(t_fern *fern)
{
	int	randnb;

	randnb = rand() % 100;
	if (randnb == 0)
	{
		fern->x[1] = 0;
		fern->y[1] = 0.16 * fern->y[0];
	}
	else if (randnb >= 1 && randnb <= 7)
	{
		fern->x[1] = -0.15 * fern->x[0] + 0.28 * fern->y[0];
		fern->y[1] = 0.26 * fern->x[0] + 0.24 * fern->y[0] + 0.44;
	}
	else if (randnb >= 8 && randnb <= 15)
	{
		fern->x[1] = 0.2 * fern->x[0] - 0.26 * fern->y[0];
		fern->y[1] = 0.23 * fern->x[0] + 0.22 * fern->y[0] + 1.6;
	}
	else
	{
		fern->x[1] = 0.85 * fern->x[0] + 0.04 * fern->y[0];
		fern->y[1] = -0.04 * fern->x[0] + 0.85 * fern->y[0] + 1.6;
	}
}
