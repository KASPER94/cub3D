/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:46:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/09/04 16:49:55 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*data(void)
{
	static t_cub	data;

	return (&data);
}

int	init_win(void)
{
	data()->mlx = mlx_init();
	if (data()->mlx == NULL)
		return (perror("mlx init"), 1);
	(data()->win) = mlx_new_window(data()->mlx, WIDTH, HEIGHT, "cub3D");
	if (data()->win == NULL)
	{
		perror("mlx_win");
		mlx_destroy_display(data()->mlx);
		free(data()->mlx);
		data()->mlx = NULL;
		return (1);
	}
	return (0);
}

int	check_macro(void)
{
	if (WIDTH <= 0 || HEIGHT <= 0)
		return (err("Screen dimensions need to be positive\n"));
	if (FOV > 130 || FOV < 30)
		return (err("FOV needs to be inferior to 130 and superior to 30\n"));
	if (ROTATION_SPEED < 0.1 || ROTATION_SPEED > 10)
		return (err("ROTATION_SPEED needs to be inferior "
				"to 10 and superior to 0.1\n"));
	if (PLAYER_SPEED < 1 || PLAYER_SPEED > 10)
		return (err("PLAYER_SPEED needs to "
				"be inferior to 10 and superior to 1\n"));
	if (MOUSE_SENSI < 0.2 || MOUSE_SENSI > 10)
		return (err("MOUSE_SENSI needs to be inferior "
				"to 10 and superior to 0.2\n"));
	return (0);
}

int	init(void)
{
	if (check_macro())
		return (1);
	set_color();
	data()->key.esc = 0;
	data()->key.w = 0;
	data()->key.s = 0;
	data()->key.a = 0;
	data()->key.d = 0;
	data()->key.left = 0;
	data()->key.right = 0;
	data()->key.p = 1;
	data()->var.run = 1;
	return (0);
}
