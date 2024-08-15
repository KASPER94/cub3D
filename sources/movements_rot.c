/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:20:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/15 11:21:23 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	player_rot_left(void)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data()->var.dirX;
	old_planex = data()->var.planeX;
	data()->var.dirX = data()->var.dirX * cos(-data()->var.rot_speed)
	- data()->var.dirY * sin(-data()->var.rot_speed);
	data()->var.dirY = old_dirx * sin(-data()->var.rot_speed)
	+ data()->var.dirY * cos(-data()->var.rot_speed);
	data()->var.planeX = data()->var.planeX * cos(-data()->var.rot_speed)
	- data()->var.planeY * sin(-data()->var.rot_speed);
	data()->var.planeY = old_planex * sin(-data()->var.rot_speed)
	+ data()->var.planeY * cos(-data()->var.rot_speed);
}

void	player_rot_right(void)
{
	double	old_diry;
	double	old_planey;

	old_diry = data()->var.dirY;
	old_planey = data()->var.planeY;
	data()->var.dirY = data()->var.dirY * cos(-data()->var.rot_speed)
	- data()->var.dirX * sin(-data()->var.rot_speed);
	data()->var.dirX = old_diry * sin(-data()->var.rot_speed)
	+ data()->var.dirX * cos(-data()->var.rot_speed);
	data()->var.planeY = data()->var.planeY * cos(-data()->var.rot_speed)
	- data()->var.planeX * sin(-data()->var.rot_speed);
	data()->var.planeX = old_planey * sin(-data()->var.rot_speed)
	+ data()->var.planeX * cos(-data()->var.rot_speed);
}
