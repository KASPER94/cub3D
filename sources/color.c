/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:26:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 12:05:22 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_rgb	*get_color(char *word)
{
	char	**colors;
	t_rgb	*value;

	value = (t_rgb *)malloc(sizeof(t_rgb));
	if (!value)
		return (NULL);
	colors = ft_split(word, ',');
	if (!colors)
		return (NULL);
	if (!check_colors(colors))
		return (free_split(colors), NULL);
	value->r = ft_atoi(colors[0]);
	value->g = ft_atoi(colors[1]);
	value->b = ft_atoi(colors[2]);
	free_split(colors);
	return (value);
}

int	fill_rgb(char *line, char id)
{
	if (id == 'c')
	{
		data()->rgb.c = get_color(line);
		if (data()->rgb.c == NULL)
			return (0);
	}
	else
	{
		data()->rgb.f = get_color(line);
		if (data()->rgb.f == NULL)
			return (0);
	}
	return (1);
}
