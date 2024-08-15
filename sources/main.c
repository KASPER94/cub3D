/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/08/15 16:44:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	if (time.tv_usec)
		ms += time.tv_usec / 1000;
	return (ms);
}

void	handle_time(void)
{
	data()->var.frame_time = ((double)get_time() / 1000.0) - data()->var.old_time;
	data()->var.old_time = get_time() / 1000.0;
}

int	start_the_game(void)
{
	void	*img;
	char	*addr;

	set_color();
	img = mlx_new_image(data()->mlx, WIDTH, HEIGHT);
	data()->img.pointer_to_img = img;
	addr = mlx_get_data_addr(data()->img.pointer_to_img,
			&data()->img.bpp, &data()->img.line_len, &data()->img.endian);
	data()->img.addr = addr;
	raycast_loop();
	handle_time();
	// data()->var.frame_time = 16 / 1000.0;
	// data()->var.run = 1;
	hooks();
	data()->var.move_speed = data()->var.frame_time * 2.5 * data()->var.run;
	data()->var.rot_speed = data()->var.frame_time * 2.5;
	mlx_put_image_to_window(data()->mlx, data()->win, img, 0, 0);
	mlx_destroy_image(data()->mlx, data()->img.pointer_to_img);
	return (0);
}

int	close_win(void)
{
	int	x;

	x = 0;
	while (x < data()->height - 1)
	{
		free(data()->map[x]);
		x++;
	}
	free(data()->map);
	mlx_destroy_window(data()->mlx, data()->win);
	mlx_destroy_display(data()->mlx);
	exit(0);
}

int	main(int ac, char **av)
{
	// leaks
	if (ac != 2)
		return (err("Error, Map isn't correct\n"), 1);
	if (init())
		return (1);
	if (parser(av[1]))
		return (1);
	if (init_win())
		return (1);
	if (init_textures())
		return (1);
	mlx_loop_hook(data()->mlx, start_the_game, NULL);
	mlx_hook(data()->win, PRESS, (1L << 0), &key_press, NULL);
	mlx_hook(data()->win, RELEASE, (1L << 1), &key_release, NULL);
	mlx_hook(data()->win, 17, 0, close_win, NULL);
	mlx_loop(data()->mlx);
	big_free();
	return (0);
}
