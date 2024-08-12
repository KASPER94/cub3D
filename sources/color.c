/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:26:44 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/12 15:43:43 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_len(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (0);
	return (i);
}

// t_rgb	*get_color(char *line)
// {
// 	char	**tmp;
// 	char	**tmp2;
// 	t_rgb	*value;

// 	value = (t_rgb *)malloc(sizeof(t_rgb));
// 	if (!value)
// 		return (NULL);
// 	tmp = ft_split(line, ' ');
// 	if (!tmp)
// 		return (NULL);
// 	tmp2 = ft_split(tmp[1], ',');
// 	if (!tmp2 || !check_len(tmp2))
// 		return (NULL);
// 	value->r = ft_atoi(tmp2[0]);
// 	value->g = ft_atoi(tmp2[1]);
// 	value->b = ft_atoi(tmp2[2]);
// 	free(tmp[0]);
// 	free(tmp);
// 	free(tmp2[0]);
// 	free(tmp2[1]);
// 	free(tmp2[2]);
// 	free(tmp2);
// 	return (value);
// }

static int	ft_isspace(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	isnum(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

t_bool	is_int(char *arg)
{
	int		i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	i++;
	while (isnum(arg[i]))
		i++;
	if (arg[i])
		return (FALSE);
	return (TRUE);
}

int	check_colors(char **colors)
{
	if (!check_len(colors))
		return (0);
	while (*colors)
	{
		// a refaire
		if (is_int(*colors) == FALSE)
			return (0);
		colors++;
	}
	return (1);
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
		return (free_split(colors), NULL);
	value->r = ft_atoi(colors[0]);
	value->g = ft_atoi(colors[1]);
	value->b = ft_atoi(colors[2]);
	free_split(colors);
	return (value);
}

int	fill_rgb(char *line, char id)
{
	if (data()->rgb == NULL)
	{
		data()->rgb = (t_color *)malloc(sizeof(t_color));
		if (data()->rgb == NULL)
			return (err("Malloc error\n"), 0);
		data()->rgb->c = NULL;
		data()->rgb->f = NULL;
	}
	if (id == 'c')
	{
		data()->rgb->c = get_color(line);
		if (data()->rgb->c == NULL)
			return (0);
	}
	else
	{
		data()->rgb->f = get_color(line);
		if (data()->rgb->f == NULL)
			return (0);
	}
	return (1);
}
