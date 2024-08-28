/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:40:55 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/28 11:41:19 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		dda_algo();
		dist_project_camera();
		set_height_wall();
		find_lowest_and_high_pix();
		coor_text();
		render_texture(x);
		x++;
	}
	return (0);
}
