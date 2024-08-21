/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:22:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/21 14:24:25 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_texture(void)
{
	if (data()->var.side == 1)
	{
		if (data()->var.stepY == -1)
			data()->var.texture_number = 1;
		else
			data()->var.texture_number = 3;
	}
	else
	{
		if (data()->var.stepX == -1)
			data()->var.texture_number = 2;
		else
			data()->var.texture_number = 0;
	}
}

void	set_values(double direction_x,
	double direction_y, double pla_x, double pla_y)
{
	data()->var.dirX = direction_x;
	data()->var.dirY = direction_y;
	data()->var.planeX = pla_x;
	data()->var.planeY = pla_y;
}

void	set_box(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.mapX = (int)tmp.position_x;
	tmp.mapY = (int)tmp.position_y;
	tmp.hit = 0;
	data()->var = tmp;
}

void	set_len_ray(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.rayDirX == 0)
		tmp.deltaDistX = 1e30;
	else
		tmp.deltaDistX = fabs(1 / data()->var.rayDirX);
	if (tmp.rayDirY == 0)
		tmp.deltaDistY = 1e30;
	else
		tmp.deltaDistY = fabs(1 / data()->var.rayDirY);
	data()->var = tmp;
}

void	set_step_and_ini_side_dist(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.rayDirX < 0)
	{
		tmp.stepX = -1;
		tmp.sideDistX = (tmp.position_x - tmp.mapX) * tmp.deltaDistX;
	}
	else
	{
		tmp.stepX = 1;
		tmp.sideDistX = (tmp.mapX + 1.0 - tmp.position_x) * tmp.deltaDistX;
	}
	if (tmp.rayDirY < 0)
	{
		tmp.stepY = -1;
		tmp.sideDistY = (tmp.position_y - tmp.mapY) * tmp.deltaDistY;
	}
	else
	{
		tmp.stepY = 1;
		tmp.sideDistY = (tmp.mapY + 1.0 - tmp.position_y) * tmp.deltaDistY;
	}
	data()->var = tmp;
}
