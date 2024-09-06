/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:20:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/09/06 18:17:22 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_mouse(void)
{
	mlx_mouse_move(data()->mlx, data()->win,
		(double)WIDTH / 2.0, (double)HEIGHT / 2.0);
}

void	player_rot_right(void)
{
	double	old_dirx;
	double	old_planex;
	double	rotation_value;

	old_dirx = data()->var.dir_x;
	old_planex = data()->var.plane_x;
	if (data()->mouse_pan_x)
	{
		rotation_value = -data()->mouse_pan_x;
		reset_mouse();
		data()->mouse_pan_x = 0;
	}
	else
		rotation_value = -data()->var.rot_speed;
	data()->var.dir_x = data()->var.dir_x * cos(rotation_value)
	- data()->var.dir_y * sin(rotation_value);
	data()->var.dir_y = old_dirx * sin(rotation_value)
	+ data()->var.dir_y * cos(rotation_value);
	data()->var.plane_x = data()->var.plane_x * cos(rotation_value)
	- data()->var.plane_y * sin(rotation_value);
	data()->var.plane_y = old_planex * sin(rotation_value)
	+ data()->var.plane_y * cos(rotation_value);
}

void	player_rot_left(void)
{
	double	old_diry;
	double	old_planey;
	double	rotation_value;

	old_diry = data()->var.dir_y;
	old_planey = data()->var.plane_y;
	if (data()->mouse_pan_x)
	{
		rotation_value = data()->mouse_pan_x;
		reset_mouse();
		data()->mouse_pan_x = 0;
	}
	else
		rotation_value = -data()->var.rot_speed;
	data()->var.dir_y = data()->var.dir_y * cos(rotation_value)
	- data()->var.dir_x * sin(rotation_value);
	data()->var.dir_x = old_diry * sin(rotation_value)
	+ data()->var.dir_x * cos(rotation_value);
	data()->var.plane_y = data()->var.plane_y * cos(rotation_value)
	- data()->var.plane_x * sin(rotation_value);
	data()->var.plane_x = old_planey * sin(rotation_value)
	+ data()->var.plane_x * cos(rotation_value);
}
