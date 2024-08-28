/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:42:03 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/28 11:43:36 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	render_texture(int x)
{
	int		y;
	int		clr;
	t_img	tex;

	y = 0;
	tex = data()->img2[data()->var.texture_number];
	my_floor(x);
	my_cell(x);
	data()->var.step = 1.0 * TEXTURE_HEIGHT / data()->var.line_height;
	data()->var.texture_position = (data()->var.draw_start - HEIGHT / 2
		+ data()->var.line_height / 2) * data()->var.step;
	y = data()->var.draw_start;
	while (y < data()->var.draw_end)
	{
		set_texture();
		data()->var.texture_y = (int)(data()->var.texture_position)
		& (tex.height - 1);
		data()->var.texture_position += data()->var.step;
		clr = (*(int *)(tex.addr + (4 * tex.width * data()->var.texture_y)
					+ 4 * data()->var.texture_x));
		mlx_place_pixel(x, y, clr);
		y++;
	}
}
