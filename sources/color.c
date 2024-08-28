/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:26:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/28 12:04:33 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	out_of_range(int number)
{
	if (number < 0 || number > 255)
		return (TRUE);
	return (FALSE);
}

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
		return (free_split(colors), free(value), NULL);
	value->r = ft_atoi(colors[0]);
	value->g = ft_atoi(colors[1]);
	value->b = ft_atoi(colors[2]);
	if (out_of_range(value->r) || out_of_range(value->g)
		|| out_of_range(value->b))
		return (free_split(colors), free(value), NULL);
	free_split(colors);
	return (value);
}

int	fill_rgb(char *line, char id)
{
	if (id == 'c')
	{
		data()->rgb.c = get_color(line);
		if (data()->rgb.c == NULL)
			return (1);
	}
	else
	{
		data()->rgb.f = get_color(line);
		if (data()->rgb.f == NULL)
			return (1);
	}
	return (0);
}
