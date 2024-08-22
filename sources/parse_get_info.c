/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:13:26 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 13:37:16 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_order(char **split)
{
	static int	i[6];

	if (!ft_strncmp(split[0], "NO", ft_strlen("NO") + 1) && i[0] == 0)
		return (++(i[0]), fill_xpm(split[1], E_NO) || 0);
	else if (!ft_strncmp(split[0], "SO", ft_strlen("SO") + 1) && i[1] == 0)
		return (++(i[1]), fill_xpm(split[1], E_SO) || 0);
	else if (!ft_strncmp(split[0], "WE", ft_strlen("WE") + 1) && i[2] == 0)
		return (++(i[2]), fill_xpm(split[1], E_WE) || 0);
	else if (!ft_strncmp(split[0], "EA", ft_strlen("EA") + 1) && i[3] == 0)
		return (++(i[3]), fill_xpm(split[1], E_EA) || 0);
	else if (!ft_strncmp(split[0], "C", ft_strlen("C") + 1) && i[4] == 0)
		return (++(i[4]), fill_rgb(split[1], 'c'));
	else if (!ft_strncmp(split[0], "F", ft_strlen("F") + 1) && i[5] == 0)
		return (++(i[5]), fill_rgb(split[1], 'f'));
	return (1);
}

char	**split_and_check_line(char *line)
{
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(line, " \f\n\r\t\v");
	free(line);
	if (tmp == NULL)
		return (perror("strtrim"), NULL);
	split = ft_split(tmp, ' ');
	if (split == NULL)
		return (perror("split"), free(tmp), NULL);
	free(tmp);
	if (split_len(split) != 2)
		return (free_split(split), NULL);
	return (split);
}

int	check_parameters(void)
{
	t_xpm	*current;
	int		count;

	count = 0;
	current = data()->xpm;
	if (data()->rgb.c == NULL || data()->rgb.f == NULL)
		return (0);
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count == 4)
		return (1);
	return (0);
}

int	get_info(int fd)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	while (line)
	{
		if (line_is_empty(line))
		{
			free (line);
			line = get_next_line(fd);
			continue ;
		}
		split = split_and_check_line(line);
		if (split == NULL)
			return (1);
		if (check_order(split) != 0)
			return (free_split(split), 1);
		if (check_parameters())
			return (free_split(split), 0);
		free_split(split);
		line = get_next_line(fd);
	}
	return (1);
}
