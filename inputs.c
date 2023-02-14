/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:54:18 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:23:40 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	keyboard_arrow_keys(int key, t_prm *prm)
{
	if (key == KEY_RIGHT)
	{
		prm->fern_xyz[X] += 50;
		prm->left += prm->temp_loc[0];
	}
	if (key == KEY_LEFT)
	{
		prm->fern_xyz[X] -= 50;
		prm->left -= prm->temp_loc[0];
	}
	if (key == KEY_UP)
	{
		prm->fern_xyz[Y] -= 50;
		prm->top -= prm->temp_loc[1];
	}
	if (key == KEY_DOWN)
	{
		prm->fern_xyz[Y] += 50;
		prm->top += prm->temp_loc[1];
	}
}

static void	keyboard_input_extension(int key, t_prm *prm)
{
	long double	left;
	long double	top;

	left = prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint));
	left = (left / (prm->win_size[X] + prm->scaleint)) * 50;
	top = prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint));
	top = (top / (prm->win_size[Y] + prm->scaleint)) * 50;
	prm->temp_loc[0] = left;
	prm->temp_loc[1] = top;
	keyboard_arrow_keys(key, prm);
	if (key == KEY_I && prm->iterations <= 1000)
		prm->iterations += 10;
	if (key == KEY_O && prm->iterations > 10)
		prm->iterations -= 10;
}

int	mouse_input(int key, int x, int y, void *ptr)
{
	t_prm		*prm;
	t_mlx		*mlx;
	long double	left;
	long double	top;

	prm = ((t_prm *)ptr);
	mlx = prm->mlx;
	prm = ((t_prm *)ptr);
	mlx_mouse_get_pos(prm->mlx->win_ptr, &x, &y);
	prm->mouse_loc[X] = x;
	prm->mouse_loc[Y] = y;
	left = (prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint)));
	top = (prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint)));
	prm->left += left / (prm->win_size[X] + prm->scaleint) * prm->mouse_loc[X];
	prm->top += top / (prm->win_size[Y] + prm->scaleint) * prm->mouse_loc[Y];
	if (key == MOUSE_SCROLL_DOWN && prm->scaleint > 1)
		prm->scaleint *= 0.5;
	if (key == MOUSE_SCROLL_UP && prm->scaleint < 13397580530642169204.0)
		prm->scaleint *= 1.5;
	left = (prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint)));
	top = (prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint)));
	prm->left -= left / (prm->win_size[X] + prm->scaleint) * prm->mouse_loc[X];
	prm->top -= top / (prm->win_size[Y] + prm->scaleint) * prm->mouse_loc[Y];
	return (0);
}

int	keyboard_input(int key, void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *)ptr);
	mlx = prm->mlx;
	if (key == KEY_R)
	{
		if (prm->bcommand == TRUE)
			prm->bcommand = FALSE;
		else
			prm->bcommand = TRUE;
	}
	else if (key == KEY_ESC)
		exit_program(NULL, FALSE);
	else
		keyboard_input_extension(key, prm);
	return (0);
}
