/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:47:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/23 12:11:55 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	cmp_coordinate(t_coordinate *a, t_coordinate b)
{
	if (a->x == b.x && a->y == b.y)
		return (0);
	return (1);
}

t_bool	has_been_visited(t_coordinate p, t_list *visited)
{
	while (visited)
	{
		if (cmp_coordinate(visited->content, p) == 0)
			return (1);
		visited = visited->next;
	}
	return (0);
}

// t_bool	not_surrounded(t_coordinate p, char	**map)
// {
// 	if (p.x == 0 || p.x == data()->height - 1)
// 		return (TRUE);
// 	if (p.y == 0 || p.y == data()->width - 1)
// 		return (TRUE);
// 	if (map[p.x - 1][p.y] == ' ' || map[p.x][p.y - 1] == ' '
// 		|| map[p.x + 1][p.y] == ' ' || map[p.x][p.y + 1] == ' ')
// 		return (TRUE);
// 	return (FALSE);
// }

t_bool	check_right(t_coordinate p, char	**map)
{
	if (map[p.x][p.y + 1] == ' ' || map[p.x][p.y + 1] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	check_left(t_coordinate p, char	**map)
{
	if (map[p.x][p.y - 1] == ' ' || map[p.x][p.y - 1] == '\0')
		return (TRUE);
	return (FALSE);
}


t_bool	check_top(t_coordinate p, char	**map)
{
	if (ft_strlen(map[p.x - 1]) < (size_t)(p.y - 1))
		return (TRUE);
	if (map[p.x - 1][p.y] == ' ' || map[p.x - 1][p.y] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	check_under(t_coordinate p, char	**map)
{
	if (ft_strlen(map[p.x + 1]) < (size_t)(p.y - 1))
		return (TRUE);
	if (map[p.x + 1][p.y] == ' ' || map[p.x + 1][p.y] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	not_surrounded(t_coordinate p, char	**map)
{
	if (p.x == 0 || p.y == 0 || p.x == data()->height)
		return (TRUE);
	if (check_right(p, map) || check_left(p, map)
		|| check_top(p, map) || check_under(p, map))
		return (TRUE);
	return (FALSE);
}
