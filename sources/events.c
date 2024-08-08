/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:43:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/08 13:44:17 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_press(int keycode)
{
	if (keycode == ESC)
		return (close_win(), 0);
	else if (keycode == W)
		data()->key.w = 1;
	else if (keycode == S)
		data()->key.s = 1;
	else if (keycode == A)
		data()->key.a = 1;
	else if (keycode == D)
		data()->key.d = 1;
	else if (keycode == LEFT)
		data()->key.left = 1;
	else if (keycode == RIGHT)
		data()->key.right = 1;
	return (0);
}

int	key_release(int keycode)
{
	if (keycode == W)
		data()->key.w = 0;
	else if (keycode == S)
		data()->key.s = 0;
	else if (keycode == A)
		data()->key.a = 0;
	else if (keycode == D)
		data()->key.d = 0;
	else if (keycode == LEFT)
		data()->key.left = 0;
	else if (keycode == RIGHT)
		data()->key.right = 0;
	return (0);
}
