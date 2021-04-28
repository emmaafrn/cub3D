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
	if (keycode == KEY_ESC)
		ft_free_n_exit(state);
	return (0);
}

inline void	d_or_a_key(t_state *state)
{
	if (state->D_key == 1)
	{
		state->player_pos.x += 0.5 * cos(state->angle);
		state->player_pos.y += 0.5 * sin(state->angle);
	}
	if (state->A_key == 1)
	{
		state->player_pos.x += -0.5 * cos(state->angle);
		state->player_pos.y += -0.5 * sin(state->angle);
	}
}

int	ft_loop(t_state *state)
{
	state->ply_temp = state->player_pos;
	if (state->D_key == 1 || state->A_key == 1)
		d_or_a_key(state);
	if (state->W_key == 1 || state->S_key == 1)
		w_or_s_key(state);
	ft_collision(state);
	jump_or_squat(state);
	if (state->up_key == 1 || state->down_key == 1)
		up_or_down(state);
	if (state->right_key == 1)
		state->angle += (5 * RAD);
	if (state->left_key == 1)
		state->angle -= (5 * RAD);
	if (state->angle == (360 * RAD))
		state->angle = 0;
	if (state->angle / RAD < 0)
		state->angle += (360 * RAD);
	distance_dividend_wall(state->player_pos, state->y_plane,
		state->parse.lenmax);
	distance_dividend_wall(state->player_pos, state->x_plane,
		state->parse.hmap);
	ft_planes_sprites(state);
	distance_dividend_sprites(state);
	pthread_mutex_lock(&state->thread_data.mutex);
	pthread_cond_broadcast(&state->render_cond);
	pthread_cond_wait(&state->thread_data.done_cond,&state->thread_data.mutex);
	mlx_put_image_to_window(state->mlx, state->win, state->img, 0, 0);
	return (0);
}
