/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:16:29 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/14 15:30:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// int	**allocate_map_track(void)
// {
// 	int	**map;
// 	int	i;

// 	i = 0;
// 	map = (int **)malloc(sizeof(int *) * data()->map_height);
// 	if (map == NULL)
// 		return (perror("malloc"), NULL);
// 	while (i < data()->map_height)
// 	{
// 		map[i] = (int *)malloc(sizeof(int) * data()->map_width);
// 		perror("malloc");
// 		if (map[i] == NULL)
// 		{
// 			while (i >= 0)
// 				free(map[i--]);
// 			return (free(map), NULL);
// 		}
// 		i++;
// 	}
// 	return (map);
// }

// int	path_checker(t_coordinate start)
// {
// 	int	**map;

// 	map = allocate_map_track();
// 	if (map == NULL)
// 		return (1);

// }

static void	clear(void *content)
{
	free(content);
}

int	cmp_coordinate(t_coordinate *a, t_coordinate b)
{
	if (a->x == b.x && a->y == b.y)
		return (0);
	return (1);
}

t_bool	has_been_visited(t_coordinate p, t_list *visited)
{
	while (visited)
	{
		if (cmp_coordinate(visited->content, p) == 0)
			return (1);
		visited = visited->next;
	}
	return (0);
}

t_bool	not_surrounded(t_coordinate p, char	**map)
{
	if (p.x == 0 || p.x == data()->height - 1)
		return (TRUE);
	if (p.y == 0 || p.y == data()->width - 1)
		return (TRUE);
	if (map[p.x - 1][p.y] == ' ' || map[p.x][p.y - 1] == ' '
		|| map[p.x + 1][p.y] == ' ' || map[p.x][p.y + 1] == ' ')
		return (TRUE);
	return (FALSE);
}

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
			return (ft_lstclear(list, &clear), free(content), 1);
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
	if (map[actual.x][actual.y] == '0' && has_been_visited(actual, *visited) == FALSE)
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x, p.y - 1);
	if (map[actual.x][actual.y] == '0' && has_been_visited(actual, *visited) == FALSE)
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x + 1, p.y);
	if (map[actual.x][actual.y] == '0' && has_been_visited(actual, *visited) == FALSE)
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	actual = init_coordinate(p.x, p.y + 1);
	if (map[actual.x][actual.y] == '0' && has_been_visited(actual, *visited) == FALSE)
		if (add_to_list(actual, queue))
			return (ft_lstclear(visited, &free), 1);
	return (0);
}

// int	add_to_visited(t_coordinate p, t_list	**visited)
// {
// 	t_list	*new;

// 	if (*visited == NULL)
// 	{
// 		*visited = ft_lstnew((void *)p);
// 		if (visited == NULL)
// 			return (1);
// 	}
// 	else
// 	{
// 		new = ft_lstnew((void *)p);
// 		if (new == NULL)
// 			return (ft_dblstclear(visited, &clear), 1);
// 		ft_lstadd_front(visited, new);
// 	}
// 	return (0);
// }

int	path_checker(t_coordinate start)
{
	//est-ce que t_coordinate a besoin d'etre malloc pour etre mis dans
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
		// ft_printf("x: %d, y: %d\n", ((t_coordinate *)(queue->content))->x, ((t_coordinate *)(queue->content))->y);
		if (check_neighb((*(t_coordinate *)queue->content), &visited, &head))
			return (1);
		queue = queue->next;
	}
	ft_lstclear(&head, &free);
	ft_lstclear(&visited, &free);
	return (0);
}
