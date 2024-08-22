/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:43:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/08/22 14:53:01 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	key_press(int keycode)
{
	if (keycode == ESC)
		return (clean_exit(), 0);
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
	else if (keycode == XK_Shift_L)
		data()->key.run = 1;
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
	else if (keycode == XK_Shift_L)
		data()->key.run = -1;
	return (0);
}

void	hooks(void)
{
	if (data()->key.run == 1)
	{
		data()->key.run = 0;
		data()->var.run = 1.5;
	}
	if (data()->key.run == -1)
	{
		data()->key.run = 0;
		data()->var.run = 1;
	}
	if (data()->key.w == 1)
		player_move_forward();
	if (data()->key.s == 1)
		player_move_backward();
	if (data()->key.a == 1)
		player_move_left();
	if (data()->key.d == 1)
		player_move_right();
	if (data()->key.left == 1 || data()->mouse_pan_x < 0)
		player_rot_left();
	if (data()->key.right == 1 || (data()->mouse_pan_x > 0))
		player_rot_right();
}
