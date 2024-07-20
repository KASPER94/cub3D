/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:50:56 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/20 23:22:28 by skapersk         ###   ########.fr       */
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

void player_rot_left(void)
{
    double oldDirX = data()->var.dirX;
    double oldPlaneX = data()->var.planeX;
    
    data()->var.dirX = data()->var.dirX * cos(-data()->var.rot_speed) - data()->var.dirY * sin(-data()->var.rot_speed);
    data()->var.dirY = oldDirX * sin(-data()->var.rot_speed) + data()->var.dirY * cos(-data()->var.rot_speed);
    data()->var.planeX = data()->var.planeX * cos(-data()->var.rot_speed) - data()->var.planeY * sin(-data()->var.rot_speed);
    data()->var.planeY = oldPlaneX * sin(-data()->var.rot_speed) + data()->var.planeY * cos(-data()->var.rot_speed);
}

void player_rot_right(void)
{
    double oldDirY = data()->var.dirY;
    double oldPlaneY = data()->var.planeY;
    
    data()->var.dirY = data()->var.dirY * cos(-data()->var.rot_speed) - data()->var.dirX * sin(-data()->var.rot_speed);
    data()->var.dirX = oldDirY * sin(-data()->var.rot_speed) + data()->var.dirX * cos(-data()->var.rot_speed);
    data()->var.planeY = data()->var.planeY * cos(-data()->var.rot_speed) - data()->var.planeX * sin(-data()->var.rot_speed);
    data()->var.planeX = oldPlaneY * sin(-data()->var.rot_speed) + data()->var.planeX * cos(-data()->var.rot_speed);
}