/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:39:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/21 17:27:21 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_path(char *path)
{
	int		test;
	char	*dup;

	if (check_format(path, "xpm"))
		return (err("Error, not xpm file\n"), NULL);
	test = open(path, O_RDONLY);
	if (test == -1)
		return (err("Error, cannot access to the xpm file\n"), NULL);
	close (test);
	dup = ft_strdup(path);
	if (dup == NULL)
		return (perror(""), NULL);
	return (dup);
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
