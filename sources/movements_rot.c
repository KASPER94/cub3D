/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:20:19 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/20 17:44:41 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	player_rot_left(void)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data()->var.dirX;
	old_planex = data()->var.planeX;
	if (data()->mouse_pan_x)
	{
		ft_putstr_fd("YOLO\n", 1);
		printf("pan x = %f\n", data()->mouse_pan_x);
		data()->var.dirX = data()->var.dirX * cos(data()->mouse_pan_x)
		- data()->var.dirY * sin(data()->mouse_pan_x);
		data()->var.dirY = old_dirx * sin(data()->mouse_pan_x)
		+ data()->var.dirY * cos(data()->mouse_pan_x);
		data()->var.planeX = data()->var.planeX * cos(data()->mouse_pan_x)
		- data()->var.planeY * sin(data()->mouse_pan_x);
		data()->var.planeY = old_planex * sin(data()->mouse_pan_x)
		+ data()->var.planeY * cos(data()->mouse_pan_x);
		mlx_mouse_move(data()->mlx, data()->win, (double)WIDTH / 2.0, (double)HEIGHT / 2.0);
		data()->mouse_pan_x = 0;
		return ;
	}
	data()->var.dirX = data()->var.dirX * cos(-data()->var.rot_speed)
	- data()->var.dirY * sin(-data()->var.rot_speed);
	data()->var.dirY = old_dirx * sin(-data()->var.rot_speed)
	+ data()->var.dirY * cos(-data()->var.rot_speed);
	data()->var.planeX = data()->var.planeX * cos(-data()->var.rot_speed)
	- data()->var.planeY * sin(-data()->var.rot_speed);
	data()->var.planeY = old_planex * sin(-data()->var.rot_speed)
	+ data()->var.planeY * cos(-data()->var.rot_speed);
}

void	player_rot_right(void)
{
	double	old_diry;
	double	old_planey;

	old_diry = data()->var.dirY;
	old_planey = data()->var.planeY;
	// if (data()->mouse_pan_x)
	// {
	// 	// ft_putstr_fd("YO\n", 1);
	// 	printf("pan x = %f\n", data()->mouse_pan_x);
	// 	data()->mouse_pan_x = -data()->mouse_pan_x;
	// 	data()->mouse = 0;
	// 	data()->var.dirY = data()->var.dirY * cos(data()->mouse_pan_x)
	// 	- data()->var.dirX * sin(data()->mouse_pan_x);
	// 	data()->var.dirX = old_diry * sin(data()->mouse_pan_x)
	// 	+ data()->var.dirX * cos(data()->mouse_pan_x);
	// 	data()->var.planeY = data()->var.planeY * cos(-data()->mouse_pan_x)
	// 	- data()->var.planeX * sin(data()->mouse_pan_x);
	// 	data()->var.planeX = old_planey * sin(data()->mouse_pan_x)
	// 	+ data()->var.planeX * cos(data()->mouse_pan_x);
	// 	mlx_mouse_move(data()->mlx, data()->win, (double)WIDTH / 2.0, (double)HEIGHT / 2.0);
	// 	data()->mouse_pan_x = 0;
	// }
	if (data()->mouse_pan_x)
	{
		// ft_putstr_fd("YO\n", 1);
		printf("pan x = %f\n", data()->mouse_pan_x);
		data()->mouse_pan_x = -data()->mouse_pan_x;
		data()->var.dirY = data()->var.dirY * cos(data()->mouse_pan_x)
		- data()->var.dirX * sin(data()->mouse_pan_x);
		data()->var.dirX = old_diry * sin(data()->mouse_pan_x)
		+ data()->var.dirX * cos(data()->mouse_pan_x);
		data()->var.planeY = data()->var.planeY * cos(data()->mouse_pan_x)
		- data()->var.planeX * sin(data()->mouse_pan_x);
		data()->var.planeX = old_planey * sin(data()->mouse_pan_x)
		+ data()->var.planeX * cos(data()->mouse_pan_x);
		mlx_mouse_move(data()->mlx, data()->win, (double)WIDTH / 2.0, (double)HEIGHT / 2.0);
		data()->mouse_pan_x = 0;
		return ;
	}
	data()->var.dirY = data()->var.dirY * cos(-data()->var.rot_speed)
	- data()->var.dirX * sin(-data()->var.rot_speed);
	data()->var.dirX = old_diry * sin(-data()->var.rot_speed)
	+ data()->var.dirX * cos(-data()->var.rot_speed);
	data()->var.planeY = data()->var.planeY * cos(-data()->var.rot_speed)
	- data()->var.planeX * sin(-data()->var.rot_speed);
	data()->var.planeX = old_planey * sin(-data()->var.rot_speed)
	+ data()->var.planeX * cos(-data()->var.rot_speed);
}

// void	player_rot_left(void)
// {
// 	double	old_dirx;
// 	double	old_planex;

// 	old_dirx = data()->var.dirX;
// 	old_planex = data()->var.planeX;
// 	if (data()->mouse)
// 	{
// 		printf("YO\n");
// 		data()->var.dirX = data()->var.dirX * cos(data()->mouse_pan_x)
// 		- data()->var.dirY * sin(data()->mouse_pan_x);
// 		data()->var.dirY = old_dirx * sin(data()->mouse_pan_x)
// 		+ data()->var.dirY * cos(data()->mouse_pan_x);
// 		data()->var.planeX = data()->var.planeX * cos(data()->mouse_pan_x)
// 		- data()->var.planeY * sin(data()->mouse_pan_x);
// 		data()->var.planeY = old_planex * sin(data()->mouse_pan_x)
// 		+ data()->var.planeY * cos(data()->mouse_pan_x);
// 		mlx_mouse_move(data()->mlx, data()->win, (double)WIDTH / 2.0, (double)HEIGHT / 2.0);
// 		data()->mouse_pan_x = 0;
// 		data()->mouse = 0;
// 		return ;
// 	}
// 	data()->var.dirX = data()->var.dirX * cos(-data()->var.rot_speed)
// 	- data()->var.dirY * sin(-data()->var.rot_speed);
// 	data()->var.dirY = old_dirx * sin(-data()->var.rot_speed)
// 	+ data()->var.dirY * cos(-data()->var.rot_speed);
// 	data()->var.planeX = data()->var.planeX * cos(-data()->var.rot_speed)
// 	- data()->var.planeY * sin(-data()->var.rot_speed);
// 	data()->var.planeY = old_planex * sin(-data()->var.rot_speed)
// 	+ data()->var.planeY * cos(-data()->var.rot_speed);
// }

// void	player_rot_right(void)
// {
// 	double	old_diry;
// 	double	old_planey;

// 	old_diry = data()->var.dirY;
// 	old_planey = data()->var.planeY;
// 	if (data()->mouse)
// 	{
// 		printf("YO\n");
// 		data()->var.dirY = data()->var.dirY * cos(-data()->mouse_pan_x)
// 		- data()->var.dirX * sin(-data()->mouse_pan_x);
// 		data()->var.dirX = old_diry * sin(-data()->mouse_pan_x)
// 		+ data()->var.dirX * cos(-data()->mouse_pan_x);
// 		data()->var.planeY = data()->var.planeY * cos(-data()->mouse_pan_x)
// 		- data()->var.planeX * sin(-data()->mouse_pan_x);
// 		data()->var.planeX = old_planey * sin(-data()->mouse_pan_x)
// 		+ data()->var.planeX * cos(-data()->mouse_pan_x);
// 		mlx_mouse_move(data()->mlx, data()->win, (double)WIDTH / 2.0, (double)HEIGHT / 2.0);
// 		data()->mouse_pan_x = 0;
// 		data()->mouse = 0;
// 		return ;
// 	}
// 	data()->var.dirY = data()->var.dirY * cos(-data()->var.rot_speed)
// 	- data()->var.dirX * sin(-data()->var.rot_speed);
// 	data()->var.dirX = old_diry * sin(-data()->var.rot_speed)
// 	+ data()->var.dirX * cos(-data()->var.rot_speed);
// 	data()->var.planeY = data()->var.planeY * cos(-data()->var.rot_speed)
// 	- data()->var.planeX * sin(-data()->var.rot_speed);
// 	data()->var.planeX = old_planey * sin(-data()->var.rot_speed)
// 	+ data()->var.planeX * cos(-data()->var.rot_speed);
// }
