/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:06:46 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/14 15:23:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// int	check_format(char *filename, char *format)
// {
// 	if (filename[0] && filename[0] == '.')
// 		filename++;
// 	while (*filename && *filename != '.')
// 		filename++;
// 	if (*filename && *filename == '.')
// 	{
// 		filename++;
// 		if (!ft_strncmp(filename, format, 4))
// 			return (0);
// 	}
// 	return (1);
// }

int	check_format(char *filename, char *format)
{
	int	i;

	i = 0;
	if (filename == NULL || format == NULL)
		return (FALSE);
	while (filename[i])
	{
		if (filename[i] == '.'
			&& !ft_strncmp(&filename[i], format, ft_strlen(format + 1)))
			return (TRUE);
		i++;
	}
	return (FALSE);
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
	// print_map();
	// util
	if (check_map())
		return (close(fd), err("Error, the map is not well formated !"));
	return (close(fd), 0);
}
