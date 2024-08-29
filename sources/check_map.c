/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:20:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/29 18:43:16 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if (value == 'W' || value == 'S' || value == 'E' || value == 'N')
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
	data()->map[start.x][start.y] = '0';
	if (path_checker(start))
		return (1);
	return (0);
}
