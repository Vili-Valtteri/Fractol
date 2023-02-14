/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:23:57 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/14 07:39:56 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_program(char *error_msg, BOOL berror)
{
	if (berror == TRUE)
		ft_putendl_fd(error_msg, 2);
	exit(0);
}
