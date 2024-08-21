/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:06:46 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/21 13:12:24 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_format(char *filename, char *format)
{
	int	i;

	i = 0;
	if (filename == NULL || format == NULL)
		return (1);
	while (filename[i])
	{
		if (filename[i] == '.'
			&& !ft_strncmp(&filename[i + 1], format, ft_strlen(format + 1)))
			return (0);
		i++;
	}
	return (1);
}

// util

void	print_map(void)
{
	char	**map;
	int		i;

	i = 0;
	map = data()->map;
	while (map[i])
	{
		ft_printf(map[i]);
		ft_printf("\n");
		i++;
	}
}

int	parser(char *filename)
{
	int	fd;

	if (check_format(filename, "cub"))
		return (err("Error, wrong file format\n"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error, cannot open the map\n"), 1);
	if (get_info(fd))
		return (err("Error, wrong information\n"));
	if (get_map(fd))
		return (close(fd), err("Error, wrong map\n"));
	if (check_map())
		return (close(fd), err("Error, the map is not well formated !"));
	return (close(fd), 0);
}
