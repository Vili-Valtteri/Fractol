/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:20:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/14 08:15:41 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	julia_check(t_prm *prm)
{
	char	*str;

	str = prm->fractol_name;
	if (ft_strcmp(str, "julia4") == 0)
	{
		prm->juliaset[X] = -0.70176;
		prm->juliaset[Y] = -0.3842;
	}
	else if (ft_strcmp(str, "julia5") == 0)
	{
		prm->juliaset[X] = -0.8;
		prm->juliaset[Y] = 0.156;
	}
}

static BOOL	which_julia(t_prm *prm)
{
	char	*str;

	str = prm->fractol_name;
	if (ft_strcmp(str, "julia1") == 0)
	{
		prm->juliaset[X] = -0.7;
		prm->juliaset[Y] = 0.27015;
	}
	else if (ft_strcmp(str, "julia2") == 0)
	{
		prm->juliaset[X] = 0.285;
		prm->juliaset[Y] = 0.01;
	}
	else if (ft_strcmp(str, "julia3") == 0)
	{
		prm->juliaset[X] = 0.285;
		prm->juliaset[Y] = 0.0;
	}
	else
		julia_check(prm);
	if (prm->juliaset[X] == 0 && prm->juliaset[Y] == 0)
		return (FALSE);
	ft_strcpy(prm->fractol_name, "juliaset");
	return (TRUE);
}

static BOOL	is_valid_fractal_name(t_prm *prm)
{
	char	*str;

	str = prm->fractol_name;
	if (ft_strcmp(str, "mandelbrot") == 0)
		return (TRUE);
	if (ft_strcmp(str, "julia") == 0)
		return (TRUE);
	if (ft_strcmp(str, "barnsleyfern") == 0)
		return (TRUE);
	return (which_julia(prm));
}

void	handle_file(char *argv, int argc, t_prm *prm)
{
	if (argc != 2)
		exit_program("julia\nmandelbrot\nbarnsleyfern\njulia1-5", TRUE);
	prm->fractol_name = &argv[0];
	if (!prm->fractol_name)
		exit_program("error", TRUE);
	ft_bzero(prm->juliaset, sizeof(prm->juliaset));
	if (is_valid_fractal_name(prm) == FALSE)
		exit_program("julia\nmandelbrot\nbarnsleyfern\njulia1-5", TRUE);
}
