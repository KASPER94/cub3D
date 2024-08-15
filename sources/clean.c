/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:06:12 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/15 12:06:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_memory(void ***str)
{
	int	i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}

void	big_free(void)
{
	destroy_xpm();
	free_memory((void ***)&data()->xpm);
	free_memory((void ***)&data()->rgb);
	free_memory((void ***)&data()->map);
}
