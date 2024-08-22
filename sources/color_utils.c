/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:28:55 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 15:41:18 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_len(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (0);
	return (i);
}

static int	ft_isspace(int c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	isnum(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

t_bool	is_int(char *arg)
{
	int		i;
	int		count;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	i++;
	count = i;
	while (isnum(arg[i]))
		i++;
	if (arg[i])
		return (FALSE);
	if (i - count > 10)
		return (FALSE);
	return (TRUE);
}

int	check_colors(char **colors)
{
	if (!check_len(colors))
		return (0);
	while (*colors)
	{
		// a refaire
		if (is_int(*colors) == FALSE)
			return (0);
		colors++;
	}
	return (1);
}
