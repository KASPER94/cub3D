/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:58 by peanut            #+#    #+#             */
/*   Updated: 2024/08/13 09:46:19 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hooks(void)
{
	if (data()->key.w == 1)
		player_move_forward();
	if (data()->key.s == 1)
		player_move_backward();
	if (data()->key.a == 1)
		player_move_left();
	if (data()->key.d == 1)
		player_move_right();
	if (data()->key.left == 1)
		player_rot_left();
	if (data()->key.right == 1)
		player_rot_right();
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
	hooks();
	data()->var.frame_time = 16 / 1000.0;
	data()->var.move_speed = data()->var.frame_time * 2.5;
	data()->var.rot_speed = data()->var.frame_time * 1.5;
	mlx_put_image_to_window(data()->mlx, data()->win, img, 0, 0);
	mlx_destroy_image(data()->mlx, data()->img.pointer_to_img);
	return (0);
}

void	free_memory(void ***str)
{
	int	i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}

void	big_free(void)
{
	free_memory((void ***)&data()->xpm);
	free_memory((void ***)&data()->rgb);
	free_memory((void ***)&data()->map);
}

char	**ft_realloc(char **map, int len)
{
	int		i;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (NULL);
	while (map[++i])
		new[i] = map[i];
	new[i] = NULL;
	new[i + 1] = NULL;
	return (free(map), new);
}

int	ft_arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
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

int main(int ac, char **av)
{
	if (ac != 2)
		return (err("Error, Map isn't correct\n"), 1);
	if (init())
		return (1);
	if (parser(av[1]))
		return (1);
	// bien free
	if (init_win())
		return (1);
	// bien free
	if (init_textures())
		return (1);
	// bien free
	mlx_loop_hook(data()->mlx, start_the_game, NULL);
	mlx_hook(data()->win, PRESS, (1L << 0), &key_press, NULL);
	mlx_hook(data()->win, RELEASE, (1L << 1), &key_release, NULL);
	mlx_loop(data()->mlx);
	big_free();
	return (0);
}
