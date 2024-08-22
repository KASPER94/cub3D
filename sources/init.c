/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:46:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 15:55:45 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	data()->win = mlx_new_window(data()->mlx, WIDTH, HEIGHT, "cub3D");
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

int	init(void)
{
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
