/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:16:29 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/29 12:07:09 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	add_to_list(t_coordinate p, t_list **list)
{
	t_list			*new;
	t_coordinate	*content;

	content = (t_coordinate *)malloc(sizeof(t_coordinate));
	if (content == NULL)
		return (perror("malloc"), 1);
	content->x = p.x;
	content->y = p.y;
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
			return (ft_lstclear(list, &free), free(content), 1);
		ft_lstadd_back(list, new);
	}
	return (0);
}

int	check_neighb(t_coordinate p, t_list **visited, t_list **queue)
{
	char			**map;
	t_coordinate	actual;

	map = data()->map;
	if (not_surrounded(p, map))
		return (ft_lstclear(visited, &free), ft_lstclear(queue, &free), 1);
	actual = init_coordinate(p.x - 1, p.y);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, *visited))
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x, p.y - 1);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, *visited))
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x + 1, p.y);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, *visited))
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x, p.y + 1);
	if (map[actual.x][actual.y] == '0' && !has_been_visited(actual, *visited))
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	return (0);
}

int	path_checker(t_coordinate start)
{
	t_list	*queue;
	t_list	*visited;
	t_list	*head;

	queue = NULL;
	visited = NULL;
	if (add_to_list(start, &queue))
		return (1);
	head = queue;
	while (queue)
	{
		if (add_to_list((*(t_coordinate *)queue->content), &visited))
			return (ft_lstclear(&head, &free), 1);
		if (check_neighb((*(t_coordinate *)queue->content), &visited, &head))
			return (1);
		queue = queue->next;
	}
	ft_lstclear(&head, &free);
	ft_lstclear(&visited, &free);
	return (0);
}
