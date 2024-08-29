/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:26:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/29 11:51:59 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	out_of_range(int number)
{
	if (number < 0 || number > 255)
		return (TRUE);
	return (FALSE);
}

char	*join_colors(char **split)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 1;
	str = ft_strdup(split[0]);
	if (str == NULL)
		return (NULL);
	while (split[i])
	{
		tmp = str;
		str = ft_strjoin(str, split[i]);
		free(tmp);
		if (str == NULL)
			return (NULL);
		i++;
	}
	return (str);
}

t_rgb	*get_color(char **split)
{
	char	**colors;
	char	*str;
	t_rgb	*value;

	value = (t_rgb *)malloc(sizeof(t_rgb));
	if (!value)
		return (NULL);
	str = join_colors(split);
	if (str == NULL)
		return (NULL);
	colors = ft_split(str, ',');
	free(str);
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

int	fill_rgb(char **split, char id)
{
	if (id == 'c')
	{
		data()->rgb.c = get_color(split);
		if (data()->rgb.c == NULL)
			return (1);
	}
	else
	{
		data()->rgb.f = get_color(split);
		if (data()->rgb.f == NULL)
			return (1);
	}
	return (0);
}
