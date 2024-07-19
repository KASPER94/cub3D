/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:50:56 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/20 01:16:50 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_move_forward(void)
{
	int x;
	int y;

	x = (int)(data()->var.position_x + data()->var.dirX * data()->var.move_speed);
	y = (int)(data()->var.position_y + data()->var.dirY * data()->var.move_speed);
	if (data()->map[x][(int)data()->var.position_y] != '1')
		data()->var.position_x += data()->var.dirX * data()->var.move_speed;
	if (data()->map[(int)data()->var.position_x][y] != '1')
		data()->var.position_y += data()->var.dirY * data()->var.move_speed;
}

void player_move_backward(void)
{
    int x;
    int y;

    x = (int)(data()->var.position_x - data()->var.dirX * data()->var.move_speed);
    y = (int)(data()->var.position_y - data()->var.dirY * data()->var.move_speed);
    if (data()->map[x][(int)data()->var.position_y] != '1')
        data()->var.position_x -= data()->var.dirX * data()->var.move_speed;
    if (data()->map[(int)data()->var.position_x][y] != '1')
        data()->var.position_y -= data()->var.dirY * data()->var.move_speed;
}