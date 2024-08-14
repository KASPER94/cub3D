/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:20:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/14 12:01:01 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_find_edge(int i)
{
	int	j;

	j = 0;
	while (data()->map[i][j] && data()->map[i][j] != '\n')
		j++;
	j--;
	while (data()->map[i][j] == ' ')
		j--;
	data()->edge.r = j;
	return (j);
}

int	check_inner(int i, int edge)
{
	int	start;

	start = data()->edge.l;
	while (data()->map[i][start] < data()->map[i][edge])
	{
		if (!ft_strchr("10NSEW", data()->map[i][start]))
			return (ft_printf("%s\n ", data()->map[i]), 0);
		start++;
	}
	return (1);
}

int	control_the_edge(int i, int j)
{
	int	count;
	int	edge;

	count = 0;
	edge = ft_find_edge(i);
	while (data()->map[i][j] && data()->map[i][j] != '\n')
	{
		if (data()->map[i][j] == ' ' && count == 0)
			j++;
		else
		{
			count++;
			data()->edge.l = j;
			if (!check_inner(i, edge))
				return (0);
			if (data()->map[i][j] != '1' && count == 1)
				return (0);
		}
		j++;
	}
	if (data()->map[i][edge] != '1')
		return (0);
	return (1);
}

int	check_border(int i)
{
	int	j;

	j = 0;
	if (i == 0 || i == data()->height)
	{
		while (data()->map[i][j] && data()->map[i][j] != '\n')
		{
			if (data()->map[i][j] != '1' && data()->map[i][j] != ' ')
				return (0);
			j++;
		}
	}
	else
		if (!control_the_edge(i, j))
			return (0);
	return (1);
}

int	check_data_map(int i)
{
	int	j;

	j = 0;
	while (data()->map[i][j] && data()->map[i][j] != '\n')
	{
		if (!ft_strchr(" 10NSEW", data()->map[i][j]))
			return (0);
		j++;
	}
	return (1);
}

t_coordinate	init_coordinate(int x, int y)
{
	t_coordinate	coordinate;

	coordinate.x = x;
	coordinate.y = y;
	coordinate.visited = FALSE;
	return (coordinate);
}

int	check_point(char **map, t_coordinate p, t_coordinate *start)
{
	char	value;

	value = map[p.x][p.y];
	if (value == 'W' || value == 'S'|| value == 'E'|| value == 'N')
	{
		if (start->x != -1)
		{
			*start = init_coordinate(-1, -1);
			return (-1);
		}
		*start = init_coordinate(p.x, p.y);
		return (0);
	}
	else if (value == '0' || value == '1' || value == ' ')
		return (0);
	else
	{
		*start = init_coordinate(-1, -1);
		return (-1);
	}
}

t_coordinate	find_starting_point(void)
{
	t_coordinate	starting_point;
	t_coordinate	actual;
	char			**map;

	map = data()->map;
	starting_point = init_coordinate(-1, -1);
	actual = init_coordinate(0, 0);
	while (actual.x < data()->height)
	{
		actual.y = 0;
		while (actual.y < data()->width && map[actual.x][actual.y])
		{
			if (check_point(map, actual, &starting_point))
				return (starting_point);
			(actual.y)++;
		}
		(actual.x)++;
	}
	return (starting_point);
}

int	check_map(void)
{
	t_coordinate	start;

	start = find_starting_point();
	if (start.x == -1)
		return (1);
	init_vectors(start.x, start.y);
	data()->map[start.x][start.y] = 0;
	if (path_checker(start))
		return (1);
	return (0);
}

// int	check_map(void)
// {
// 	int	i;
// 	int	j;
// 	int	count;

// 	i = -1;
// 	count = 0;
// 	while (data()->map[++i])
// 	{
// 		if (!check_border(i) || !check_data_map(i))
// 			return (0);
// 		j = -1;
// 		while (data()->map[i][++j])
// 		{
// 			if (data()->map[i][j] == 'N' || data()->map[i][j] == 'S'
// 				|| data()->map[i][j] == 'E' || data()->map[i][j] == 'W')
// 			{
// 				init_vectors(i, j);
// 				data()->map[i][j] = 0;
// 				count++;
// 			}
// 		}
// 	}
// 	if (count > 1)
// 		return (0);
// 	return (count);
// }
