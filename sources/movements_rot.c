/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:20:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/21 12:59:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	reset_mouse(void)
{
	mlx_mouse_move(data()->mlx, data()->win,
		(double)WIDTH / 2.0, (double)HEIGHT / 2.0);
}

void	player_rot_left(void)
{
	double	old_dirx;
	double	old_planex;
	double	rotation_value;

	old_dirx = data()->var.dirX;
	old_planex = data()->var.planeX;
	if (data()->mouse_pan_x)
	{
		rotation_value = data()->mouse_pan_x;
		reset_mouse();
		data()->mouse_pan_x = 0;
	}
	else
		rotation_value = -data()->var.rot_speed;
	data()->var.dirX = data()->var.dirX * cos(rotation_value)
	- data()->var.dirY * sin(rotation_value);
	data()->var.dirY = old_dirx * sin(rotation_value)
	+ data()->var.dirY * cos(rotation_value);
	data()->var.planeX = data()->var.planeX * cos(rotation_value)
	- data()->var.planeY * sin(rotation_value);
	data()->var.planeY = old_planex * sin(rotation_value)
	+ data()->var.planeY * cos(rotation_value);
}

void	player_rot_right(void)
{
	double	old_diry;
	double	old_planey;
	double	rotation_value;

	old_diry = data()->var.dirY;
	old_planey = data()->var.planeY;
	if (data()->mouse_pan_x)
	{
		rotation_value = -data()->mouse_pan_x;
		reset_mouse();
		data()->mouse_pan_x = 0;
	}
	else
		rotation_value = -data()->var.rot_speed;
	data()->var.dirY = data()->var.dirY * cos(rotation_value)
	- data()->var.dirX * sin(rotation_value);
	data()->var.dirX = old_diry * sin(rotation_value)
	+ data()->var.dirX * cos(rotation_value);
	data()->var.planeY = data()->var.planeY * cos(rotation_value)
	- data()->var.planeX * sin(rotation_value);
	data()->var.planeX = old_planey * sin(rotation_value)
	+ data()->var.planeX * cos(rotation_value);
}
