/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:46:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/08 13:46:55 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub	*data(void)
{
	static t_cub	data;

	return (&data);
}

void	init_data(void)
{
	t_cub	*d;

	d = data();
	d->mlx = NULL;
	d->win = NULL;
	d->var = (t_var){0};
	d->img = (t_img){0};
	d->color = malloc(sizeof(t_color) * 3);
	if (!d->color)
	{
		perror("Error allocating memory for colors");
		exit(EXIT_FAILURE);
	}
	d->map = NULL;
	d->width = 0;
	d->height = 0;
}

int	init_win(void)
{
	void	*tmp;
	t_img	*img_ptr;

	data()->mlx = mlx_init();
	tmp = mlx_new_window(data()->mlx, WIDTH, HEIGHT, "cub3D");
	img_ptr = (t_img *)malloc(sizeof(t_img));
	if (img_ptr == NULL)
		return (err("Malloc error\n"), 1);
	data()->img = *img_ptr;
	free(img_ptr);
	img_ptr = (t_img *)malloc(sizeof(t_img));
	if (img_ptr == NULL)
		return (err("Malloc error\n"), 1);
	data()->txt = *img_ptr;
	free(img_ptr);
	data()->win = tmp;
	return (0);
}

int	init(void)
{
	data()->player = (t_player *)malloc(sizeof(t_player));
	if (data()->player == NULL)
		return (err("Malloc error for player\n"), 1);
	data()->key.esc = 0;
	data()->key.w = 0;
	data()->key.s = 0;
	data()->key.a = 0;
	data()->key.d = 0;
	data()->key.left = 0;
	data()->key.right = 0;
	data()->key.p = 1;
	return (0);
}
