/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:19:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/28 11:55:44 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_color(void)
{
	data()->color.blue.r = 80;
	data()->color.blue.g = 91;
	data()->color.blue.b = 166;
	data()->color.red.r = 175;
	data()->color.red.g = 54;
	data()->color.red.b = 60;
	data()->color.green.r = 70;
	data()->color.green.g = 148;
	data()->color.green.b = 73;
	data()->color.white.r = 255;
	data()->color.white.g = 255;
	data()->color.white.b = 255;
	data()->color.yellow.r = 255;
	data()->color.yellow.g = 223;
	data()->color.yellow.b = 0;
}

void	mlx_place_pixel(int x, int y, int color)
{
	char	*distance;

	distance = data()->img.addr
		+ (y * data()->img.line_len + x * (data()->img.bpp / 8));
	*(unsigned int *)distance = color;
}

void	draw_wall(int x)
{
	int	y;
	int	color;

	if (data()->var.side == 1)
	{
		if (data()->var.step_y == -1)
			color = (data()->color.red.r << 16
					| data()->color.red.g << 8 | data()->color.red.b);
		else
			color = (data()->color.green.r << 16
					| data()->color.green.g << 8 | data()->color.green.b);
	}
	else
	{
		if (data()->var.step_x == -1)
			color = (data()->color.blue.r << 16
					| data()->color.blue.g << 8 | data()->color.blue.b);
		else
			color = (data()->color.green.r << 16
					| data()->color.green.g << 8 | data()->color.green.b);
	}
	y = data()->var.draw_start;
	while (y < data()->var.draw_end)
		mlx_place_pixel(x, y++, color);
}

void	my_floor(int x)
{
	int	color;
	int	y;

	color = (data()->rgb.f->r << 16 | data()->rgb.f->g << 8
			| data()->rgb.f->b);
	y = data()->var.draw_start;
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

	color = (data()->rgb.c->r << 16 | data()->rgb.c->g << 8
			| data()->rgb.c->b);
	y = 0;
	while (y < data()->var.draw_end)
	{
		mlx_place_pixel(x, y, color);
		y++;
	}
}
