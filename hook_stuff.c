/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:58:54 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:58:55 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdint.h>

int	key_hook(int keycode, t_state *state)
{
	if (keycode == KEY_D)
		state->D_key = 1;
	if (keycode == KEY_A)
		state->A_key = 1;
	if (keycode == KEY_W)
		state->W_key = 1;
	if (keycode == KEY_S)
		state->S_key = 1;
	if (keycode == KEY_RIGHT)
		state->right_key = 1;
	if (keycode == KEY_LEFT)
		state->left_key = 1;
	if (keycode == KEY_UP)
		state->up_key = 1;
	if (keycode == KEY_DOWN)
		state->down_key = 1;
	if (keycode == KEY_SPACE)
		state->space_key = 1;
	if (keycode == KEY_C)
		state->c_key = 1;
	if (keycode == KEY_LESS)
		state->less_key = 1;
	if (keycode == KEY_MORE)
		state->more_key = 1;
	if (keycode == KEY_ESC)
		ft_free_n_exit(state);
	return (0);
}

int	release_key(int keycode, t_state *state)
{
	if (keycode == KEY_D)
		state->D_key = 0;
	if (keycode == KEY_A)
		state->A_key = 0;
	if (keycode == KEY_W)
		state->W_key = 0;
	if (keycode == KEY_S)
		state->S_key = 0;
	if (keycode == KEY_RIGHT)
		state->right_key = 0;
	if (keycode == KEY_LEFT)
		state->left_key = 0;
	if (keycode == KEY_UP)
		state->up_key = 0;
	if (keycode == KEY_DOWN)
		state->down_key = 0;
	if (keycode == KEY_SPACE)
		state->space_key = 0;
	if (keycode == KEY_C)
		state->c_key = 0;
	if (keycode == KEY_LESS)
		state->less_key = 0;
	if (keycode == KEY_MORE)
		state->more_key = 0;
	if (keycode == KEY_ESC)
		ft_free_n_exit(state);
	return (0);
}
