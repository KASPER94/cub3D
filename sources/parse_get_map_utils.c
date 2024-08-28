/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:00:12 by skapersk          #+#    #+#             */
/*   Updated: 2024/08/28 12:01:24 by skapersk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void	reverse_map(void)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = data()->height - 1;
	while (i < j)
	{
		temp = data()->map[i];
		data()->map[i] = data()->map[j];
		data()->map[j] = temp;
		i++;
		j--;
	}
}
