/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:14:16 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/14 10:58:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	add_new_line(char *line)
{
	char	**tmp;
	int		arr_len;

	arr_len = ft_arr_len(data()->map);
	if (!arr_len)
		return (1);
	tmp = ft_realloc(data()->map, arr_len + 2);
	if (!tmp)
		return (big_free(), 1);
	data()->map = tmp;
	data()->map[arr_len] = ft_strdup(line);
	if (!data()->map[arr_len])
		return (big_free(), 1);
	return (0);
}

int	fill_map(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n");
	if (tmp == NULL)
		return (1);
	if (!data()->map)
	{
		data()->map = malloc(sizeof(char *) * 2);
		if (!data()->map)
			return (1);
		data()->map[0] = ft_strdup(tmp);
		if (!data()->map[0])
			return (1);
		data()->map[1] = NULL;
	}
	else
		if (add_new_line(tmp))
			return (1);
	return (0);
}

int	check_logic_fits(char *line)
{
	static int	i;
	int			x;

	x = 0;
	if (data()->map && data()->map[i])
	{
		while (line[x] && (line[x] != '1'))
			x++;
		if (data()->map[i][x] == '1'
			|| (data()->map[i][x - 1] && data()->map[i][x - 1] == '1')
			|| (data()->map[i][x + 1] && data()->map[i][x + 1] == '1'))
			return (0);
		i++;
	}
	return (1);
}

int	get_width(char *line)
{
	int	max_width;
	int	i;

	max_width = 0;
	i = 0;
	while (line[i])
	{
		max_width = i;
		i++;
	}
	if (max_width > data()->width)
		data()->width = max_width;
	// if (!check_logic_fits(line))
	//     return (0);
	return (1);
}

char	*skip_empty(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line_is_empty(line) == TRUE)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	check_end(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line_is_empty(line) == FALSE)
			return (free(line), 1);
		free (line);
		line = get_next_line(fd);
	}
	return (0);
}

int	get_map(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = skip_empty(fd);
	if (line == NULL)
		return (1);
	while (line)
	{
		if (line_is_empty(line))
		{
			free(line);
			break ;
		}
		if (fill_map(line))
			return (1);
		if (!get_width(line))
			return (1);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data()->height = i;
	return (check_end(fd));
}

// int	get_map(int fd)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		tmp = ft_strtrim(line, " \f\n\r\t\v");
// 		if (ft_strlen(tmp) > 0)
// 			if (fill_map(line))
// 				return (1);
// 		if (!get_width(line))
// 			return (1);
// 		free(line);
// 		i++;
// 		line = get_next_line(fd);
// 	}
// 	data()->height = i;
// 	return (0);
// }
