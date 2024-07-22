/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:50:56 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/22 11:25:22 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_move_forward(void)
{
    int new_x = (int)(data()->var.position_x + data()->var.dirX * data()->var.move_speed);
    int new_y = (int)(data()->var.position_y + data()->var.dirY * data()->var.move_speed);

    if (data()->map[new_x][(int)data()->var.position_y] != '1')
        data()->var.position_x += data()->var.dirX * data()->var.move_speed;
    if (data()->map[(int)data()->var.position_x][new_y] != '1')
        data()->var.position_y += data()->var.dirY * data()->var.move_speed;
}

void player_move_backward(void)
{
    int new_x = (int)(data()->var.position_x - data()->var.dirX * data()->var.move_speed);
    int new_y = (int)(data()->var.position_y - data()->var.dirY * data()->var.move_speed);

    if (data()->map[new_x][(int)data()->var.position_y] != '1')
        data()->var.position_x -= data()->var.dirX * data()->var.move_speed;
    if (data()->map[(int)data()->var.position_x][new_y] != '1')
        data()->var.position_y -= data()->var.dirY * data()->var.move_speed;
}

void player_move_right(void)
{
    int new_x = (int)(data()->var.position_x - data()->var.dirY * data()->var.move_speed);
    int new_y = (int)(data()->var.position_y + data()->var.dirX * data()->var.move_speed);

    if (data()->map[new_x][(int)data()->var.position_y] != '1')
        data()->var.position_x -= data()->var.dirY * data()->var.move_speed;
    if (data()->map[(int)data()->var.position_x][new_y] != '1')
        data()->var.position_y += data()->var.dirX * data()->var.move_speed;
}

void player_move_left(void)
{
    int new_x = (int)(data()->var.position_x + data()->var.dirY * data()->var.move_speed);
    int new_y = (int)(data()->var.position_y - data()->var.dirX * data()->var.move_speed);

    if (data()->map[new_x][(int)data()->var.position_y] != '1')
        data()->var.position_x += data()->var.dirY * data()->var.move_speed;
    if (data()->map[(int)data()->var.position_x][new_y] != '1')
        data()->var.position_y -= data()->var.dirX * data()->var.move_speed;
}

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
