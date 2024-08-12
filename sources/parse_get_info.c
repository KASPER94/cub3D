/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:13:26 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/12 15:46:08 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_path(char *path)
{
	int		test;

	if (check_format(path, "xpm"))
		return (err("Error, not xpm file\n"), NULL);
	test = open(path, O_RDONLY);
	if (test == -1)
		return (err("Error, cannot access to the xpm file\n"), NULL);
	close (test);
	return (path);
}

void	add_xpm(t_xpm **lst, t_xpm *new)
{
	t_xpm	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

int	fill_xpm(char *path, t_type_xpm type)
{
	t_xpm	*new;

	new = (t_xpm *)malloc(sizeof(t_xpm));
	if (!new)
		return (1);
	new->type = type;
	new->val = get_path(path);
	if (new->val == NULL)
		return (free(new), 1);
	new->next = NULL;
	add_xpm(&(data()->xpm), new);
	return (0);
}

// int	check_order(char *line)
// {
// 	static int	i;

// 	if (!ft_strncmp(line, "NO", ft_strlen("NO")))
// 		return (fill_xpm(line, E_NO), ++i);
// 	else if (!ft_strncmp(line, "SO", ft_strlen("SO")))
// 		return (fill_xpm(line, E_SO), ++i);
// 	else if (!ft_strncmp(line, "WE", ft_strlen("WE")))
// 		return (fill_xpm(line, E_WE), ++i);
// 	else if (!ft_strncmp(line, "EA", ft_strlen("EA")))
// 		return (fill_xpm(line, E_EA), ++i);
// 	else if (line[0] == 'C' && fill_rgb(line, 'c'))
// 		return (++i);
// 	else if (line[0] == 'F' && fill_rgb(line, 'f'))
// 		return (++i);
// 	else if (!ft_strncmp(line, "", ft_strlen ("")))
// 		return (1);
// 	else if (line[0] == 'F' || line[0] == 'C'
// 		|| !ft_strncmp(line, "EA", ft_strlen("EA"))
// 		|| !ft_strncmp(line, "WE", ft_strlen("WE"))
// 		|| !ft_strncmp(line, "SO", ft_strlen("SO"))
// 		|| !ft_strncmp(line, "NO", ft_strlen("NO")))
// 		return (0);
// 	return (0);
// }

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
	else if (!ft_strncmp(split[0], "C", ft_strlen("C") + 1) && i[4] == 0
		&& fill_rgb(split[1], 'c'))
		return (++(i[4]), 0);
	else if (!ft_strncmp(split[0], "F", ft_strlen("F") + 1) && i[5] == 0
		&& fill_rgb(split[1], 'f'))
		return (++(i[5]), 0);
	return (1);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
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

static int	is_space(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}

t_bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
	{
		if (line[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	check_parameters(void)
{
	t_xpm	*current;
	int		count;

	count = 0;
	current = data()->xpm;
	if (data()->rgb == NULL || data()->rgb->c == NULL || data()->rgb->f == NULL)
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
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

// int	get_info(int fd)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		status;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		tmp = ft_strtrim(line, " \f\n\r\t\v");
// 		status = check_order(tmp);
// 		if (!status)
// 			return (free(tmp), free(line), 1);
// 		else if (status == 6)
// 			return (free(tmp), free(line), 0);
// 		free(tmp);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (1);
// }
