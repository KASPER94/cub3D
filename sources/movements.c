/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:50:56 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/22 15:04:13 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(void)
{
	int	new_x;
	int	new_y;

	new_x = (int)(data()->var.position_x + data()->var.dirX
			* data()->var.move_speed);
	new_y = (int)(data()->var.position_y + data()->var.dirY
			* data()->var.move_speed);
	if (data()->map[new_x][(int)data()->var.position_y] != '1')
		data()->var.position_x += data()->var.dirX * data()->var.move_speed;
	if (data()->map[(int)data()->var.position_x][new_y] != '1')
		data()->var.position_y += data()->var.dirY * data()->var.move_speed;
}

void	player_move_backward(void)
{
	int	new_x;
	int	new_y;

	new_x = (int)(data()->var.position_x - data()->var.dirX
			* data()->var.move_speed);
	new_y = (int)(data()->var.position_y - data()->var.dirY
			* data()->var.move_speed);
	if (data()->map[new_x][(int)data()->var.position_y] != '1')
		data()->var.position_x -= data()->var.dirX * data()->var.move_speed;
	if (data()->map[(int)data()->var.position_x][new_y] != '1')
		data()->var.position_y -= data()->var.dirY * data()->var.move_speed;
}

void	player_move_right(void)
{
	int	new_x;
	int	new_y;

	new_x = (int)(data()->var.position_x - data()->var.dirY
			* data()->var.move_speed);
	new_y = (int)(data()->var.position_y + data()->var.dirX
			* data()->var.move_speed);
	if (data()->map[new_x][(int)data()->var.position_y] != '1')
		data()->var.position_x -= data()->var.dirY * data()->var.move_speed;
	if (data()->map[(int)data()->var.position_x][new_y] != '1')
		data()->var.position_y += data()->var.dirX * data()->var.move_speed;
}

void	player_move_left(void)
{
	int	new_x;
	int	new_y;

	new_x = (int)(data()->var.position_x + data()->var.dirY
			* data()->var.move_speed);
	new_y = (int)(data()->var.position_y - data()->var.dirX
			* data()->var.move_speed);
	if (data()->map[new_x][(int)data()->var.position_y] != '1')
		data()->var.position_x += data()->var.dirY * data()->var.move_speed;
	if (data()->map[(int)data()->var.position_x][new_y] != '1')
		data()->var.position_y -= data()->var.dirX * data()->var.move_speed;
}
