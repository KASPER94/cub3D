/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/23 10:14:38 by skapersk         ###   ########.fr       */
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
	data()->var.rayDirX = data()->var.dirX
	+ data()->var.planeX * data()->var.camera;
	data()->var.rayDirY = data()->var.dirY
	+ data()->var.planeY * data()->var.camera;
}

void	DDA(void)
{
	while (data()->var.hit == 0)
	{
		if (data()->var.sideDistX < data()->var.sideDistY)
		{
			data()->var.sideDistX += data()->var.deltaDistX;
			data()->var.mapX += data()->var.stepX;
			data()->var.side = 0;
		}
		else
		{
			data()->var.sideDistY += data()->var.deltaDistY;
			data()->var.mapY += data()->var.stepY;
			data()->var.side = 1;
		}
		if (data()->var.mapY < 0.25 || data()->var.mapX < 0.25
			|| data()->var.mapY > data()->width - 0.25
			|| data()->var.mapX > data()->height - 1.25)
			data()->var.hit = 1;
		if (data()->map[data()->var.mapX][data()->var.mapY] == '1')
			data()->var.hit = 1;
	}
}

void	dist_project_camera(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.side == 0)
		tmp.perpWallDist = (tmp.sideDistX - tmp.deltaDistX);
	else
		tmp.perpWallDist = (tmp.sideDistY - tmp.deltaDistY);
	data()->var = tmp;
}

void	set_height_wall(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.lineHeight = (int)(HEIGHT / tmp.perpWallDist);
	data()->var = tmp;
}

void	find_lowest_and_high_pix(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.drawStart = -tmp.lineHeight / 2 + HEIGHT / 2;
	if (tmp.drawStart < 0)
		tmp.drawStart = 0;
	tmp.drawEnd = tmp.lineHeight / 2 + HEIGHT / 2;
	if (tmp.drawEnd >= HEIGHT)
		tmp.drawEnd = HEIGHT - 1;
	data()->var = tmp;
}

void	coor_text(void)
{
	if (data()->var.side == 0)
		data()->var.wall = data()->var.position_y + data()->var.perpWallDist *  data()->var.rayDirY;
	else
		data()->var.wall = data()->var.position_x + data()->var.perpWallDist *  data()->var.rayDirX;
	data()->var.wall -= floor(data()->var.wall);
	data()->var.texture_x = (int)(data()->var.wall * (double)TEXTURE_WIDTH);
	if (data()->var.side == 0 && data()->var.rayDirX > 0)
		data()->var.texture_x = TEXTURE_WIDTH - data()->var.texture_x - 1;
	if (data()->var.side == 1 && data()->var.rayDirY < 0)
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
	step = 1.0 * TEXTURE_HEIGHT / data()->var.lineHeight;
	// Position initiale de la texture
	texture_position = (data()->var.drawStart - HEIGHT / 2 + data()->var.lineHeight / 2) * step;

	y = data()->var.drawStart;
	while (y < data()->var.drawEnd) {
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
