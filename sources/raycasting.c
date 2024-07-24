/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:33:01 by skapersk          #+#    #+#             */
/*   Updated: 2024/07/24 16:51:35 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

void	set_texture(void)
{
	if (data()->var.side == 0)
	{
		if (data()->var.mapY > data()->var.position_y)
			data()->var.texture_number = 1;
		else
			data()->var.texture_number = 3;
	}
	else
	{
		if (data()->var.mapX > data()->var.position_x)
			data()->var.texture_number = 2;
		else
			data()->var.texture_number = 0;
	}
}

void	set_values(double direction_x, double direction_y, double pla_x, double pla_y)
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

void	set_box(void)
{
	t_var	tmp;

	tmp = data()->var;
	tmp.mapX = (int)tmp.position_x;
	tmp.mapY = (int)tmp.position_y;
	tmp.hit = 0;
	data()->var = tmp;
}

void set_len_ray(void)
{
	t_var	tmp;

	tmp = data()->var;
	if (tmp.rayDirX == 0)
		tmp.deltaDistX = 1e30;
	else
		tmp.deltaDistX = sqrt(1 + (tmp.rayDirY * tmp.rayDirY) / (tmp.rayDirX * tmp.rayDirX));
	if (tmp.rayDirY == 0)
		tmp.deltaDistY = 1e30;
	else
		tmp.deltaDistY = sqrt(1 + (tmp.rayDirX * tmp.rayDirX) / (tmp.rayDirY * tmp.rayDirY));
	data()->var = tmp;
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
	data()->var = tmp;
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
			|| data()->var.mapY > data()->width - 1.25
			|| data()->var.mapX > data()->height - 0.25)
			break ;
		else if (data()->map[data()->var.mapX][data()->var.mapY] > '0')
		{
			data()->var.hit = 1;
			set_texture();
		}
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

void	calcul_wall_value(void)
{
	if (data()->var.side == 1)
	{
        data()->var.wall = (data()->var.stepY == -1) ? 0 : 1;
    }
	else
	{
        data()->var.wall = (data()->var.stepX == -1) ? 2 : 3;
    }
	// if (data()->var.side == 0)
	// {
	// 	data()->var.wall = data()->var.position_y
	// 	+ data()->var.perpWallDist * data()->var.rayDirY;
	// }
	// else
	// {
	// 	data()->var.wall = data()->var.position_x
	// 	+ data()->var.perpWallDist * data()->var.rayDirX;
	// }
	// data()->var.wall -= floor(data()->var.wall);
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

	// int	tex;

	// tex = (int)(data()->var.wall * (double)TEXTURE_WIDTH);
	// if (data()->var.side == 0)
	// {
	// 	tex = TEXTURE_WIDTH - tex - 1;
	// }
	// if (data()->var.side == 1)
	// {
	// 	tex = TEXTURE_WIDTH - tex - 1;
	// }
	// data()->var.texture_x = tex;
}


// void	coor_text(void)
// {
// 	int	tex;

// 	tex =(int)(data()->var.wall * (double)TEXTURE_WIDTH);
// 	if (data()->var.side == 0 && data()->var.rayDirX > 0)
// 		tex = TEXTURE_WIDTH - data()->var.texture_x - 1;
// 	if (data()->var.side == 1 && data()->var.rayDirY < 0)
// 		tex = TEXTURE_WIDTH - data()->var.texture_x - 1;
// 	data()->var.texture_x = tex;
// }

void	set_color(void)
{
	data()->color = malloc(sizeof(t_test_color));
	data()->color->blue.r = 80;
	data()->color->blue.g = 91;
	data()->color->blue.b = 166;
	data()->color->red.r = 175;
	data()->color->red.g = 54;
	data()->color->red.b = 60;
	data()->color->green.r = 70;
	data()->color->green.g = 148;
	data()->color->green.b = 73;
	data()->color->white.r = 255;
	data()->color->white.g = 255;
	data()->color->white.b = 255;
	data()->color->yellow.r = 255;
	data()->color->yellow.g = 223;
	data()->color->yellow.b = 0;
}

void	mlx_place_pixel(int x, int y, int color)
{
	char	*distance;

	distance = data()->img.addr + (y * data()->img.line_len + x * (data()->img.bpp / 8));
	*(unsigned int *)distance = color;
}

void	draw_wall(int x)
{
	int	y;
	int	color;

	if (data()->var.side == 1)
	{
		color = (data()->var.stepY == -1) ? (data()->color->red.r << 16 | data()->color->red.g << 8 | data()->color->red.b)
										: (data()->color->green.r << 16 | data()->color->green.g << 8 | data()->color->green.b);
	}
	else
	{
		color = (data()->var.stepX == -1) ? (data()->color->blue.r << 16 | data()->color->blue.g << 8 | data()->color->blue.b)
										: (data()->color->green.r << 16 | data()->color->green.g << 8 | data()->color->green.b);
	}
	y = data()->var.drawStart;
	while (y < data()->var.drawEnd)
	{
		mlx_place_pixel(x, y, color);
		y++;
	}
}

void	my_floor(int x)
{
	int	color;
	int	y;

	color = (data()->rgb->f->r << 16 | data()->rgb->f->g << 8 | data()->rgb->f->b);
	y = data()->var.drawStart;
	while (y < HEIGHT - 1)
	{
		mlx_place_pixel(x, y, color);
		y++;
	}
}

void	my_cell(int x)
{
	int	color;
	int	y;

	color = (data()->rgb->c->r << 16 | data()->rgb->c->g << 8 | data()->rgb->c->b);
	y = 0;
	while (y < data()->var.drawEnd)
	{
		mlx_place_pixel(x, y, color);
		y++;
	}
}

void draw_vertical_texture_stripe(int x)
{
    double step;
    double textures_position;
    int y;


	calcul_wall_value();
    // Calcul du step pour l'incrémentation de la position dans la texture
    step = 1.0 * TEXTURE_HEIGHT / data()->var.lineHeight;
    textures_position = (data()->var.drawStart - HEIGHT / 2 + data()->var.lineHeight / 2) * step;
    my_floor(x);
    my_cell(x);
    y = data()->var.drawStart;
    while (y < data()->var.drawEnd) {
        // Calcul de la coordonnée y de la texture
        data()->var.texture_y = (int)textures_position & (TEXTURE_HEIGHT - 1);
        textures_position += step;

        // Placement du pixel avec la couleur de la texture
        int color = (*(int *)(data()->img2[data()->var.wall].addr + (4 * data()->img2[1].width * data()->var.texture_y) + 4 * data()->var.texture_x));
        if (data()->var.side == 1) {
            color = (color >> 1) & 8355711; // Appliquer une ombre pour les côtés
        }
        mlx_place_pixel(x, y, color);
        y++;
    }
}


// void	draw_vertical_texture_stripe(int x)
// {
// 	double	step;
// 	double	textures_position;
// 	int		y;

// 	int	wall;


// 	if (data()->var.side == 1)
// 	{
// 		wall = (data()->var.stepY == -1) ? 0 : 1;
// 	}
// 	else
// 	{
// 		wall = (data()->var.stepX == -1) ? 2 : 3;
// 	}
// 	y = data()->var.drawStart;
// 	step = 1.0 * TEXTURE_HEIGHT / data()->var.lineHeight;
// 	textures_position = (data()->var.drawStart - HEIGHT / 2 + data()->var.lineHeight / 2) * step;
// 	my_floor(x);
// 	my_cell(x);4 * data()->img2[1].width * y_tex
// 	while (y < data()->var.drawEnd)
// 	{
// 		data()->var.texture_y = (int)textures_position & (TEXTURE_HEIGHT - 1);
// 		mlx_place_pixel(x, y, data()->textures[wall][TEXTURE_HEIGHT * data()->var.texture_y + data()->var.texture_x]);
// 		y++;
// 	}

/*

	step = 1.0 * TEXTURE_HEIGHT / data()->var.lineHeight;
	textures_position = (data()->var.drawStart - HEIGHT / 2 + data()->var.lineHeight / 2) * step;
	y = data()->var.drawStart;
	while (y < data()->var.drawEnd)
	{
		data()->var.texture_y = (int)textures_position & (TEXTURE_HEIGHT - 1);
		textures_position += step;
		data()->var.color = data()->textures[data()->var.texture_number][TEXTURE_HEIGHT * data()->var.texture_y + data()->var.texture_x];
		if (data()->var.side == 1)
			data()->var.color = (data()->var.color >> 1) & 8355711;
		mlx_place_pixel(x, y, data()->var.color);
		y++;
	}*/
// }





// void temp(int x) {
// 	int y = 0;

// 	t_img	tex;
//     void *addr;
// 	tex = data()->img2[1];
// 	addr = tex.addr;
// 	int x_tex;
// 	int y_tex;
// 	int clr;
// 	my_floor(x);
//     my_cell(x);
//     y = data()->var.drawStart;
// 	printf("%d\n", data()->var.mapX);
//     while (y < data()->var.drawEnd) {
// 		x_tex = (double)x / 1900.0 * tex.width;
// 		y_tex = (double)y / data()->var.drawEnd * tex.height;
// 		// printf("%f\n", x_tex);
// 		// printf("%f\n\n", y / 200.0);
// 		clr = (*(int *)(addr + (4 * tex.width * y_tex) + 4 * x_tex));

// 		mlx_place_pixel(x, y, clr);
// 		y++;
// 	}
// }

void temp(int x) {
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
	step = 1.0 * tex.height / data()->var.lineHeight;
	// Position initiale de la texture
	texture_position = (data()->var.drawStart - HEIGHT / 2 + data()->var.lineHeight / 2) * step;

    y = data()->var.drawStart;
    while (y < data()->var.drawEnd) {
		x_tex = (double)x / WIDTH * tex.width;
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
		set_step_and_ini_sideDist();
		DDA();
		dist_project_camera();
		set_height_wall();
		find_lowest_and_high_pix();
		coor_text();
		// draw_vertical_texture_stripe(x);
		// draw_wall(x);
		temp(x);
		x++;
	}
	return (0);
}


// #include "cub3d.h"

// void	set_values(double direction_x, double direction_y, double pla_x,
// 		double pla_y)
// {
// 	data()->var.dirX = direction_x;
// 	data()->var.dirY = direction_y;
// 	data()->var.planeX = pla_x;
// 	data()->var.planeY = pla_y;
// }

// void	init_vectors(int x, int y)
// {
// 	data()->var.position_x = x + 0.5;
// 	data()->var.position_y = y + 0.5;
// 	if (data()->map[x][y] == 'N')
// 		set_values(0, -1, 0.66, 0);
// 	else if (data()->map[x][y] == 'S')
// 		set_values(0, 1, -0.66, 0);
// 	else if (data()->map[x][y] == 'E')
// 		set_values(1, 0, 0, 0.66);
// 	else if (data()->map[x][y] == 'W')
// 		set_values(-1, 0, 0, -0.66);
// }

// void	find_ray_and_dir(int x, int w)
// {
// 	data()->var.camera = 2 * x / (double)w - 1;
// 	data()->var.rayDirX = data()->var.dirX + data()->var.planeX * data()->var.camera;
// 	data()->var.rayDirY = data()->var.dirY + data()->var.planeY * data()->var.camera;
// }

// void	set_box(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	tmp.mapX = (int)tmp.position_x;
// 	tmp.mapY = (int)tmp.position_y;
// 	tmp.hit = 0;
// 	data()->var = tmp;
// }

// void set_len_ray(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	if (tmp.rayDirX == 0)
// 		tmp.deltaDistX = 1e30;
// 	else
// 		tmp.deltaDistX = fabs(1 / tmp.rayDirX);
// 	if (tmp.rayDirY == 0)
// 		tmp.deltaDistY = 1e30;
// 	else
// 		tmp.deltaDistY = fabs(1 / tmp.rayDirY);
// 	data()->var = tmp;
// }

// void	set_step_and_ini_sideDist(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	if (tmp.rayDirX < 0)
//       {
//         tmp.stepX = -1;
//         tmp.sideDistX = (tmp.position_x - tmp.mapX) * tmp.deltaDistX;
//       }
//       else
//       {
//         tmp.stepX = 1;
//         tmp.sideDistX = (tmp.mapX + 1.0 - tmp.position_x) * tmp.deltaDistX;
//       }
//       if (tmp.rayDirY < 0)
//       {
//         tmp.stepY = -1;
//         tmp.sideDistY = (tmp.position_y - tmp.mapY) * tmp.deltaDistY;
//       }
//       else
//       {
//         tmp.stepY = 1;
//         tmp.sideDistY = (tmp.mapY + 1.0 - tmp.position_y) * tmp.deltaDistY;
//       }
// 	data()->var = tmp;
// }

// void	DDA(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	while (tmp.hit == 0)
// 	{
// 		if (tmp.sideDistX < tmp.sideDistY)
// 		{
// 			tmp.sideDistX += tmp.deltaDistX;
// 			tmp.mapX += tmp.stepX;
// 			tmp.side = 0;
// 		}
// 		else
// 		{
// 			tmp.sideDistY += tmp.deltaDistY;
// 			tmp.mapY += tmp.stepY;
// 			tmp.side = 1;
// 		}
// 		if (data()->map[tmp.mapX][tmp.mapY] > 0)
// 			tmp.hit = 1;
// 	}
// 	data()->var = tmp;
// }

// void	dist_project_camera(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	if (tmp.side == 0)
// 		tmp.perpWallDist = (tmp.sideDistX - tmp.deltaDistX);
// 	else
// 		tmp.perpWallDist = (tmp.sideDistY - tmp.deltaDistY);
// 	data()->var = tmp;
// }

// void	set_height_wall(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	tmp.lineHeight = (int)(HEIGHT / tmp.perpWallDist);
// 	data()->var = tmp;
// 	// ft_printf("%d ..... ", data()->var.lineHeight);
// }

// void	find_lowest_and_high_pix(void)
// {
// 	t_var	tmp;

// 	tmp = data()->var;
// 	tmp.drawStart = -tmp.lineHeight / 2 + HEIGHT / 2;
// 	if (tmp.drawStart < 0)
// 		tmp.drawStart = 0;
// 	tmp.drawEnd = tmp.lineHeight / 2 + HEIGHT / 2;
// 	if (tmp.drawEnd >= HEIGHT)
// 		tmp.drawEnd = HEIGHT - 1;
// 	data()->var = tmp;
// 	// ft_printf("%d ..... ", tmp.drawStart);
// 	// ft_printf("%d\n", tmp.lineHeight);
// }

// void	set_color(void)
// {
// 	data()->color = malloc(sizeof(t_test_color));
// 	data()->color->blue.r = 80;
// 	data()->color->blue.g = 91;
// 	data()->color->blue.b = 166;
// 	data()->color->red.r = 175;
// 	data()->color->red.g = 54;
// 	data()->color->red.b = 60;
// 	data()->color->green.r = 70;
// 	data()->color->green.g = 148;
// 	data()->color->green.b = 73;
// 	    // Ceiling color
//     data()->color->white.r = 255;
//     data()->color->white.g = 255;
//     data()->color->white.b = 255;

//     // Wall color
//     data()->color->yellow.r = 255;
//     data()->color->yellow.g = 223;
//     data()->color->yellow.b = 0;
// }

// void	mlx_place_pixel(int x, int y, int colour)
// {
// 	char	*distance;

// 	distance = data()->img.addr + (y * data()->img.line_len + x * (data()->img.bpp / 8));
// 	*(unsigned int *)distance = colour;
// }

// void	draw_wall(int x)
// {
// 	int	y;
// 	int	color;

// 	if (data()->var.side == 1)
// 	{
//         color = (data()->var.stepY == -1) ? (data()->color->red.r << 16 | data()->color->red.g << 8 | data()->color->red.b)
//                                   : (data()->color->green.r << 16 | data()->color->green.g << 8 | data()->color->green.b);
// 	}
// 	else
// 	{
//         color = (data()->var.stepX == -1) ? (data()->color->blue.r << 16 | data()->color->blue.g << 8 | data()->color->blue.b)
//                                   : (data()->color->green.r << 16 | data()->color->green.g << 8 | data()->color->green.b);
// 	}
// 	y = data()->var.drawStart;
// 	// ft_printf("%d --- %d\n", y, data()->var.drawEnd);
// 	while (y < data()->var.drawEnd)
// 	{
// 		mlx_place_pixel(x, y, color);
// 		y++;
// 	}
// }

// int	raycast_loop(void)
// {
// 	int	x;
// 	int	i;

// 	x = 0;
// 	i = 0;
// 	while (x < WIDTH)
// 	{
// 		find_ray_and_dir(x, WIDTH);
// 		set_box();
// 		set_len_ray();
// 		set_step_and_ini_sideDist();
// 		DDA();
// 		dist_project_camera();
// 		set_height_wall();
// 		find_lowest_and_high_pix();
// 		draw_wall(x);
// 		x++;
// 	}
// 	return (i);
// }
