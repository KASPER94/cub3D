/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:36:09 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/21 14:30:51 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	is_space(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (TRUE);
	return (FALSE);
}

t_bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
	{
		if (line[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	ft_arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
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
