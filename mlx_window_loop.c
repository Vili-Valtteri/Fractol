/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:56:19 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/12 08:16:50 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mlx_window_loop(void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *) ptr);
	mlx = prm->mlx;
	fractol(prm);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
	return (0);
}
