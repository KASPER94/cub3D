/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:06:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/28 11:58:48 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_xpm(void)
{
	t_xpm	*list;
	t_xpm	*next;

	list = data()->xpm;
	while (list)
	{
		next = list->next;
		free(list->val);
		free(list);
		list = next;
	}
	data()->xpm = NULL;
}

void	destroy_map(void)
{
	if (data()->map)
	{
		free_split(data()->map);
		data()->map = NULL;
	}
}

void	destroy_imgs(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data()->img2[i].pointer_to_img)
		{
			mlx_destroy_image(data()->mlx, data()->img2[i].pointer_to_img);
			data()->img2[i].pointer_to_img = NULL;
		}
		i++;
	}
}

void	destroy_colors(void)
{
	if (data()->rgb.c)
	{
		free(data()->rgb.c);
		data()->rgb.c = NULL;
	}
	if (data()->rgb.f)
	{
		free(data()->rgb.f);
		data()->rgb.f = NULL;
	}
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
