/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:47:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/15 12:47:30 by cdeville         ###   ########.fr       */
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

t_bool	not_surrounded(t_coordinate p, char	**map)
{
	if (p.x == 0 || p.x == data()->height - 1)
		return (TRUE);
	if (p.y == 0 || p.y == data()->width - 1)
		return (TRUE);
	if (map[p.x - 1][p.y] == ' ' || map[p.x][p.y - 1] == ' '
		|| map[p.x + 1][p.y] == ' ' || map[p.x][p.y + 1] == ' ')
		return (TRUE);
	return (FALSE);
}
