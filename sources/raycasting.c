/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/27 14:32:11 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vectors(int x, int y)
{
	data()->var.position_x = x + 0.5;
	data()->var.position_y = y + 0.5;
	if (data()->map[x][y] == 'N')
		set_values(0, -1, 0.66, 0);
	else if (data()->map[x][y] == 'S')
		set_values(0, 1, -0.66, 0);
	else if (data()->map[x][y] == 'E')
		set_values(1, 0, 0, 0.66);
	else if (data()->map[x][y] == 'W')
		set_values(-1, 0, 0, -0.66);
}

void	find_ray_and_dir(int x, int w)
{
	data()->var.camera = 2 * x / (double)w - 1;
	data()->var.ray_dir_x = data()->var.dir_x
	+ data()->var.plane_x * data()->var.camera;
	data()->var.ray_dir_y = data()->var.dir_y
	+ data()->var.plane_y * data()->var.camera;
}

void	DDA(void)
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

void	find_lowest_and_high_pix(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.draw_start = -tmp.line_height / 2 + HEIGHT / 2;
	if (tmp.draw_start < 0)
		tmp.draw_start = 0;
	tmp.draw_end = tmp.line_height / 2 + HEIGHT / 2;
	if (tmp.draw_end >= HEIGHT)
		tmp.draw_end = HEIGHT - 1;
	data()->var = tmp;
}

void	coor_text(void)
{
	if (data()->var.side == 0)
		data()->var.wall = data()->var.position_y
		+ data()->var.perp_wall_dist * data()->var.ray_dir_y;
	else
		data()->var.wall = data()->var.position_x
		+ data()->var.perp_wall_dist * data()->var.ray_dir_x;
	data()->var.wall -= floor(data()->var.wall);
	data()->var.texture_x = (int)(data()->var.wall * (double)TEXTURE_WIDTH);
	if (data()->var.side == 0 && data()->var.ray_dir_x > 0)
		data()->var.texture_x = TEXTURE_WIDTH - data()->var.texture_x - 1;
	if (data()->var.side == 1 && data()->var.ray_dir_y < 0)
		data()->var.texture_x = TEXTURE_WIDTH - data()->var.texture_x - 1;
}

void temp(int x)
{
	int y = 0;

	t_img tex;
	void *addr;
	tex = data()->img2[data()->var.texture_number];
	addr = tex.addr;
	int x_tex;
	int y_tex;
	int clr;
	double step;
	double texture_position;

	my_floor(x);
	my_cell(x);
	// Calcul du step pour l'incrémentation de la position dans la texture
	step = 1.0 * TEXTURE_HEIGHT / data()->var.line_height;
	// Position initiale de la texture
	texture_position = (data()->var.draw_start - HEIGHT / 2 + data()->var.line_height / 2) * step;

	y = data()->var.draw_start;
	while (y < data()->var.draw_end) {
		set_texture();
		x_tex = data()->var.texture_x ;
		y_tex = (int)texture_position & (tex.height - 1);
		texture_position += step;
		clr = (*(int *)(addr + (4 * tex.width * y_tex) + 4 * x_tex));

		mlx_place_pixel(x, y, clr);
		y++;
	}
}

int	raycast_loop(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		find_ray_and_dir(x, WIDTH);
		set_box();
		set_len_ray();
		set_step_and_ini_side_dist();
		DDA();
		dist_project_camera();
		set_height_wall();
		find_lowest_and_high_pix();
		coor_text();
		temp(x);
		x++;
	}
	return (0);
}
