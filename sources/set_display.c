/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:22:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/27 14:56:13 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_texture(void)
{
	if (data()->var.side == 1)
	{
		if (data()->var.step_y == -1)
			data()->var.texture_number = 1;
		else
			data()->var.texture_number = 3;
	}
	else
	{
		if (data()->var.step_x == -1)
			data()->var.texture_number = 2;
		else
			data()->var.texture_number = 0;
	}
}

void	set_values(double direction_x,
	double direction_y, double pla_x, double pla_y)
{
	data()->var.dir_x = direction_x;
	data()->var.dir_y = direction_y;
	data()->var.plane_x = pla_x;
	data()->var.plane_y = pla_y;
}

void	set_box(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.map_x = (int)tmp.position_x;
	tmp.map_y = (int)tmp.position_y;
	tmp.hit = 0;
	data()->var = tmp;
}

void	set_len_ray(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.ray_dir_x == 0)
		tmp.delta_dist_x = 1e30;
	else
		tmp.delta_dist_x = fabs(1 / data()->var.ray_dir_x);
	if (tmp.ray_dir_y == 0)
		tmp.delta_dist_y = 1e30;
	else
		tmp.delta_dist_y = fabs(1 / data()->var.ray_dir_y);
	data()->var = tmp;
}

void	set_step_and_ini_side_dist(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.ray_dir_x < 0)
	{
		tmp.step_x = -1;
		tmp.side_dist_x = (tmp.position_x - tmp.map_x) * tmp.delta_dist_x;
	}
	else
	{
		tmp.step_x = 1;
		tmp.side_dist_x = (tmp.map_x + 1.0 - tmp.position_x) * tmp.delta_dist_x;
	}
	if (tmp.ray_dir_y < 0)
	{
		tmp.step_y = -1;
		tmp.side_dist_y = (tmp.position_y - tmp.map_y) * tmp.delta_dist_y;
	}
	else
	{
		tmp.step_y = 1;
		tmp.side_dist_y = (tmp.map_y + 1.0 - tmp.position_y) * tmp.delta_dist_y;
	}
	data()->var = tmp;
}
