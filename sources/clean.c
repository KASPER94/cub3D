/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:06:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 15:01:38 by cdeville         ###   ########.fr       */
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
