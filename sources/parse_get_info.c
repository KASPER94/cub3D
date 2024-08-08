/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:13:26 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/08 14:43:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_path(char *line)
{
	char	**tmp;
	char	*tmp2;
	int		test;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (NULL);
	tmp2 = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp);
	if (check_format(tmp2, "xpm"))
		return (free(tmp2), err("Error, not xpm file\n"), NULL);
	test = open(tmp2, O_RDONLY);
	if (test == -1)
		return (err("Error, cannot access to the xpm file\n"), free(tmp2), NULL);
	close (test);
	return (tmp2);
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

int	fill_xpm(char *line, t_type_xpm type)
{
	t_xpm	*new;

	new = (t_xpm *)malloc(sizeof(t_xpm));
	if (!new)
		return (0);
	new->type = type;
	new->val = get_path(line);
	if (new->val == NULL)
		return (0);
	new->next = NULL;
	add_xpm(&(data()->xpm), new);
	return (1);
}

int	check_order(char *line)
{
	static int	i;

	if (!ft_strncmp(line, "NO", ft_strlen("NO")))
		return (fill_xpm(line, E_NO), ++i);
	else if (!ft_strncmp(line, "SO", ft_strlen("SO")))
		return (fill_xpm(line, E_SO), ++i);
	else if (!ft_strncmp(line, "WE", ft_strlen("WE")))
		return (fill_xpm(line, E_WE), ++i);
	else if (!ft_strncmp(line, "EA", ft_strlen("EA")))
		return (fill_xpm(line, E_EA), ++i);
	else if (line[0] == 'C' && fill_rgb(line, 'c'))
		return (++i);
	else if (line[0] == 'F' && fill_rgb(line, 'f'))
		return (++i);
	else if (!ft_strncmp(line, "", ft_strlen ("")))
		return (1);
	else if (line[0] == 'F' || line[0] == 'C'
		|| !ft_strncmp(line, "EA", ft_strlen("EA"))
		|| !ft_strncmp(line, "WE", ft_strlen("WE"))
		|| !ft_strncmp(line, "SO", ft_strlen("SO"))
		|| !ft_strncmp(line, "NO", ft_strlen("NO")))
		return (0);
	return (0);
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

int	get_info(int fd)
{
	char	*line;
	char	*tmp;
	char	**split;

	line = get_next_line(fd);
	while (line)
	{
		split = split_and_check_line(line);
		if (split == NULL)
			return (1);
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
