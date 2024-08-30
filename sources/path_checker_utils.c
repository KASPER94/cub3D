/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:47:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/30 11:14:24 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	has_been_visited(t_coordinate p, char **visited)
{
	if (visited[p.x][p.y] == '1')
		return (TRUE);
	return (FALSE);
}

t_bool	not_surrounded(t_coordinate p, char	**map)
{
	if (p.x == 0 || p.y == 0 || p.x == data()->height - 1)
		return (TRUE);
	if (check_right(p, map) || check_left(p, map)
		|| check_top(p, map) || check_under(p, map))
		return (TRUE);
	return (FALSE);
}
