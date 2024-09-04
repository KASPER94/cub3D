/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/09/04 16:33:20 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vectors(int x, int y)
{
	double	plane;

	plane = tan((double)FOV * (M_PI / 180.0) / 2.0);
	data()->var.position_x = x + 0.5;
	data()->var.position_y = y + 0.5;
	if (data()->map[x][y] == 'E')
		set_values(0, -1, plane, 0);
	else if (data()->map[x][y] == 'W')
		set_values(0, 1, -plane, 0);
	else if (data()->map[x][y] == 'S')
		set_values(1, 0, 0, plane);
	else if (data()->map[x][y] == 'N')
		set_values(-1, 0, 0, -plane);
}

void	find_ray_and_dir(int x, int w)
{
	data()->var.camera = 2 * x / (double)w - 1;
	data()->var.ray_dir_x = data()->var.dir_x
	+ data()->var.plane_x * data()->var.camera;
	data()->var.ray_dir_y = data()->var.dir_y
	+ data()->var.plane_y * data()->var.camera;
}

void	dda_algo(void)
{
	while (data()->var.hit == 0)
	{
		if (data()->var.side_dist_x < data()->var.side_dist_y)
		{
			data()->var.side_dist_x += data()->var.delta_dist_x;
			data()->var.map_x += data()->var.step_x;
			data()->var.side = 0;
		}
		else
		{
			data()->var.side_dist_y += data()->var.delta_dist_y;
			data()->var.map_y += data()->var.step_y;
			data()->var.side = 1;
		}
		if (data()->var.map_y < 0.25 || data()->var.map_x < 0.25
			|| data()->var.map_y > data()->width - 0.25
			|| data()->var.map_x > data()->height - 1.25)
			data()->var.hit = 1;
		if (data()->map[data()->var.map_x][data()->var.map_y] == '1')
			data()->var.hit = 1;
	}
}

void	dist_project_camera(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.side == 0)
		tmp.perp_wall_dist = (tmp.side_dist_x - tmp.delta_dist_x);
	else
		tmp.perp_wall_dist = (tmp.side_dist_y - tmp.delta_dist_y);
	data()->var = tmp;
}

void	set_height_wall(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.line_height = (int)(HEIGHT / tmp.perp_wall_dist);
	data()->var = tmp;
}
