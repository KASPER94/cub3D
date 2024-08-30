/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:03:11 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/30 11:18:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
