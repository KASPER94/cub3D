/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skapersk <skapersk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:06:46 by cdeville          #+#    #+#             */
/*   Updated: 2024/09/05 15:41:12 by skapersk         ###   ########.fr       */
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

void	read_all(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	parser(char *filename)
{
	int	fd;

	if (check_format(filename, "cub"))
		return (err("wrong file format\n"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("cannot open the map\n"), 1);
	if (get_info(fd))
		return (read_all(fd), close(fd), err("wrong information\n"));
	if (get_map(fd))
		return (read_all(fd),
			close(fd), err("wrong map\n"));
	if (check_map())
		return (read_all(fd), close(fd),
			err("the map is not well formated !\n"));
	return (close(fd), 0);
}
