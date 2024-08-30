/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:16:29 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/30 11:00:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_visited(char **visited, t_coordinate p)
{
	visited[p.x][p.y] = '1';
}

int	add_to_list(t_coordinate p, t_list **list, char **visited)
{
	t_list			*new;
	t_coordinate	*content;
	t_list			*tmp;

	set_visited(visited, p);
	content = (t_coordinate *)malloc(sizeof(t_coordinate));
	if (content == NULL)
		return (perror("malloc"), 1);
	*content = init_coordinate(p.x, p.y);
	if (*list == NULL)
	{
		*list = ft_lstnew(content);
		if (list == NULL)
			return (free(content), 1);
	}
	else
	{
		new = ft_lstnew(content);
		if (new == NULL)
			return (free(content), 1);
		tmp = (*list)->next;
		(*list)->next = new;
		new->next = tmp;
	}
	return (0);
}

int	check_neighb(t_coordinate p, char **visited, t_list **queue)
{
	char			**map;
	t_coordinate	actual;

	map = data()->map;
	if (not_surrounded(p, map))
		return (free_split(visited), 1);
	actual = init_coordinate(p.x - 1, p.y);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, visited))
		if (add_to_list(actual, queue, visited))
			return (free_split(visited), 1);
	actual = init_coordinate(p.x, p.y - 1);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, visited))
		if (add_to_list(actual, queue, visited))
			return (free_split(visited), 1);
	actual = init_coordinate(p.x + 1, p.y);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, visited))
		if (add_to_list(actual, queue, visited))
			return (free_split(visited), 1);
	actual = init_coordinate(p.x, p.y + 1);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, visited))
		if (add_to_list(actual, queue, visited))
			return (free_split(visited), 1);
	return (0);
}

char	**copy_empty_map(char **map)
{
	char	**visited;
	int		i;
	int		len;

	i = 0;
	visited = (char **)malloc(sizeof(char *) *(split_len(map) + 1));
	if (visited == NULL)
		return (NULL);
	visited[split_len(map)] = NULL;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		visited[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (visited[i] == NULL)
			return (free_split(visited), NULL);
		ft_bzero(visited[i], len + 1);
		i++;
	}
	return (visited);
}

int	path_checker(t_coordinate start)
{
	t_list	*queue;
	char	**visited;
	t_list	*actual;

	queue = NULL;
	visited = copy_empty_map(data()->map);
	if (add_to_list(start, &queue, visited))
		return (1);
	actual = queue;
	if (visited == NULL)
		return (ft_lstclear(&queue, &free), 1);
	while (actual)
	{
		set_visited(visited, (*(t_coordinate *)actual->content));
		if (check_neighb((*(t_coordinate *)actual->content), visited, &actual))
			return (ft_lstclear(&queue, &free), 1);
		actual = actual->next;
	}
	ft_lstclear(&queue, &free);
	free_split(visited);
	return (0);
}
