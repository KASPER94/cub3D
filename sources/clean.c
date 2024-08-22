/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:06:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 12:22:00 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_xpm(void)
{
	t_xpm	*list;
	t_xpm	*next;

	list = data()->xpm;
	while (list)
	{
		next = list->next;
		free(list->val);
		free(list);
		list = next;
	}
	data()->xpm = NULL;
}
