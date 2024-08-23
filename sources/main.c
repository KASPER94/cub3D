/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/08/22 15:57:25 by cdeville         ###   ########.fr       */
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
	data()->var.frame_time = ((double)get_time() / 1000.0)
		- data()->var.old_time;
	data()->var.old_time = get_time() / 1000.0;
}

int	start_the_game(void)
{
	void	*img;
	char	*addr;

	img = mlx_new_image(data()->mlx, WIDTH, HEIGHT);
	data()->img.pointer_to_img = img;
	addr = mlx_get_data_addr(data()->img.pointer_to_img,
			&data()->img.bpp, &data()->img.line_len, &data()->img.endian);
	data()->img.addr = addr;
	raycast_loop();
	handle_time();
	hooks();
	data()->var.move_speed = data()->var.frame_time * 2.5 * data()->var.run;
	data()->var.rot_speed = data()->var.frame_time * 2.5;
	mlx_put_image_to_window(data()->mlx, data()->win, img, 0, 0);
	mlx_destroy_image(data()->mlx, data()->img.pointer_to_img);
	return (0);
}

// int	mouse_event(int x, int y, void *param)
// {
// 	// double	*add_x;
// 	// if (data()->mouse)
// 	// 	return (0);
// 	// data()->mouse = 1;
// 	// data()->mouse_pan_x =  (double)(x - WIDTH / 2) / (WIDTH / 2);
// 	// // data()->mouse_pan_x = x;
// 	// printf("y = %d\n", y);
// 	// data()->mouse_pan_y = (HEIGHT / 2) / (double)(y - HEIGHT / 2) * 0.0001;
// 	// mlx_mouse_move(data()->mlx, data()->win, WIDTH / 2, HEIGHT / 2);
// 	// mlx_mouse_move(data()->mlx, data()->win, WIDTH, 0);
// 	// (void)param;
// 	// (void)x;
// 	// add_x = (double *)param;
// 	// if (*add_x)
// 	// 	return (0);
// 	if (data()->mouse)
// 		return (0);
// 	data()->mouse = 1;
// 	data()->mouse_pan_x = (double)(x - WIDTH / 2) / (WIDTH / 2);
// 	// *add_x =  (double)(x - WIDTH / 2) / (WIDTH / 2);
// 	// // data()->mouse_pan_x = x;
// 	printf("x = %d\nPan x = %f\n", x, data()->mouse_pan_x );
// 	(void)y;
// 	// data->mouse_pan_x = (HEIGHT / 2) / (double)(y - HEIGHT / 2) * 0.0001;
// 	// mlx_mouse_move(data()->mlx, data()->win, WIDTH / 2, HEIGHT / 2);
// 	// // mlx_mouse_move(data()->mlx, data()->win, WIDTH, 0);
// 	// (void)y;
// 	(void)param;
// 	return (0);
// }

int	mouse_event(int x, int y, void *param)
{
	t_cub	*data;

	data = param;
	data->mouse_pan_x = (x -(WIDTH / 2.0)) / (WIDTH / 2.0)
		* M_PI  * data->var.frame_time * (MOUSE_SENSI * 10);
	(void)param;
	(void)y;
	return (0);
}

int	clean_exit(void)
{
	destroy_map();
	destroy_xpm();
	destroy_imgs();
	if (data()->win && data()->mlx)
	{
		mlx_destroy_window(data()->mlx, data()->win);
		data()->win = NULL;
	}
	if (data()->mlx)
	{
		mlx_destroy_display(data()->mlx);
		free(data()->mlx);
		data()->mlx = NULL;
	}
	destroy_colors();
	exit(0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (err("Error, Map isn't correct\n"), 1);
	init();
	if (parser(av[1]))
		return (clean_exit(), 1);
	if (init_win())
		return (clean_exit(), 1);
	if (init_textures())
		return (clean_exit(), 1);
	mlx_mouse_hide(data()->mlx, data()->win);
	mlx_loop_hook(data()->mlx, start_the_game, NULL);
	mlx_hook(data()->win, 6, (1L << 6), &mouse_event, (data()));
	mlx_hook(data()->win, PRESS, (1L << 0), &key_press, NULL);
	mlx_hook(data()->win, RELEASE, (1L << 1), &key_release, NULL);
	mlx_hook(data()->win, 17, 0, clean_exit, NULL);
	mlx_loop(data()->mlx);
	return (0);
}
