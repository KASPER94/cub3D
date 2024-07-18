/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/18 14:48:25 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_values(double direction_x, double direction_y, double pla_x,
		double pla_y)
{
	data()->var.dirX = direction_x;
	data()->var.dirY = direction_y;
	data()->var.planeX = pla_x;
	data()->var.planeY = pla_y;
}

void	init_vectors(int x, int y)
{
	data()->var.position_x = x + 0.5;
	data()->var.position_y = y + 0.5;
	if (data()->map[y][x] == 'N')
		set_values(0, -1, 0.66, 0);
	else if (data()->map[y][x] == 'S')
		set_values(0, 1, -0.66, 0);
	else if (data()->map[y][x] == 'E')
		set_values(1, 0, 0, 0.66);
	else if (data()->map[y][x] == 'W')
		set_values(-1, 0, 0, -0.66);
}

void	find_ray_and_dir(int x)
{
	data()->var.camera = 2 * x / (double)WIDTH - 1;
	data()->var.rayDirX = data()->var.dirX + data()->var.planeX * data()->var.camera;
	data()->var.rayDirY = data()->var.dirY + data()->var.planeY * data()->var.camera;
}

int	raycast_loop(void)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		find_ray_and_dir(x);
	}
	return (i);
}