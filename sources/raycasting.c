/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/18 17:55:29 by skapersk         ###   ########.fr       */
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

void	set_box(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.mapX = (int)tmp.position_x;
	tmp.mapY = (int)tmp.position_y;
	tmp.hit = 0;
}

void set_len_ray(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.rayDirX == 0)
		tmp.deltaDistX = 1e30;
	else
		tmp.deltaDistX = fabs(1 / tmp.rayDirX);
	if (tmp.rayDirY == 0)
		tmp.deltaDistY = 1e30;
	else
		tmp.deltaDistY = fabs(1 / tmp.rayDirY);
}

void	set_step_and_ini_sideDist(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.rayDirX < 0)
      {
        tmp.stepX = -1;
        tmp.sideDistX = (tmp.position_x - tmp.mapX) * tmp.deltaDistX;
      }
      else
      {
        tmp.stepX = 1;
        tmp.sideDistX = (tmp.mapX + 1.0 - tmp.position_x) * tmp.deltaDistX;
      }
      if (tmp.rayDirY < 0)
      {
        tmp.stepY = -1;
        tmp.sideDistY = (tmp.position_y - tmp.mapY) * tmp.deltaDistY;
      }
      else
      {
        tmp.stepY = 1;
        tmp.sideDistY = (tmp.mapY + 1.0 - tmp.position_y) * tmp.deltaDistY;
      }
}

void	DDA(void)
{
	t_var	tmp;

	tmp = data()->var;
	while (tmp.hit == 0)
	{
		if (tmp.sideDistX < tmp.sideDistY)
		{
			tmp.sideDistX += tmp.deltaDistX;
			tmp.mapX += tmp.stepX;
			tmp.side = 0;
		}
		else
		{
			tmp.sideDistY += tmp.deltaDistY;
			tmp.mapY += tmp.stepY;
			tmp.side = 1;
		}
		if (data()->map[tmp.mapX][tmp.mapY] > 0)
			tmp.hit = 1;
	}
}

void	dist_project_camera(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.side == 0)
		tmp.perpWallDist = (tmp.sideDistX - tmp.deltaDistX);
	else
		tmp.perpWallDist = (tmp.sideDistX - tmp.deltaDistX);
}

void	set_height_wall(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.lineHeight = (int)(data()->height / tmp.perpWallDist);
}

void	find_lowest_and_high_pix(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.drawStart = -tmp.lineHeight / 2 + data()->height / 2;
	if (tmp.drawStart < 0)
		tmp.drawStart = 0;
	tmp.drawEnd = tmp.lineHeight / 2 + data()->height / 2;
	if (tmp.drawEnd >= data()->height)
		tmp.drawEnd = data()->height - 1;
}

void	set_color(void)
{
	data()->color->blue.r = 80;
	data()->color->blue.g = 91;
	data()->color->blue.b = 166;
	data()->color->red.r = 175;
	data()->color->red.g = 54;
	data()->color->red.b = 60;
	data()->color->green.r = 70;
	data()->color->green.g = 148;
	data()->color->green.b = 73;

}

void init_image(void)
{
	t_img img;

	img = data()->img;

    img.pointer_to_img = mlx_new_image(data()->mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.pointer_to_img, &img.bpp, &img.line_len, &img.endian);
}


void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void	draw_wall(int x)
{
    t_var tmp = data()->var;
    int y;
    int color;

    // Choisissez la couleur en fonction de la direction du mur
    if (tmp.side == 1)
        color = 0xFF0000; // Rouge pour les murs verticaux
    else
        color = 0x00FF00; // Vert pour les murs horizontaux

    y = tmp.drawStart;
    while (y < tmp.drawEnd)
    {
        my_mlx_pixel_put(&data()->img, x, y, color);
        y++;
    }
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
		set_box();
		set_len_ray();
		set_step_and_ini_sideDist();
		DDA();
		dist_project_camera();
		set_height_wall();
		find_lowest_and_high_pix();
		// set_color();
		draw_wall(x);
		x++;
	}
	ft_printf("--- %p --- \n", data()->img.pointer_to_img);
	mlx_put_image_to_window(data()->mlx, data()->win, data()->img.pointer_to_img, 0, 0);
	return (i);
}