#include "cub3d.h"

int	key_hook(int keycode, t_state *state)
{
	// printf("keycode = %d\n", keycode);
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
	if (keycode == KEY_ESC)
		exit(0);
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
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	d_or_a_key(t_state *state)
{
	if (state->D_key == 1)
	{
		if (state->player_pos.x < state->parse.lenmax)
		{
			state->player_pos.x += 0.5 * cos(state->angle);
			state->player_pos.y += 0.5 * sin(state->angle);
		}
	}
	if (state->A_key == 1)
	{
		if (state->player_pos.x > 0)
		{
			state->player_pos.x += -0.5 * cos(state->angle);
			state->player_pos.y += -0.5 * sin(state->angle);
		}
	}
}

void	w_or_s_key(t_state *state)
{
	if (state->W_key == 1)
	{
		if (state->player_pos.y > 0)
		{
			state->player_pos.x += -0.5 * -sin(state->angle);
			state->player_pos.y += -0.5 * cos(state->angle);
		}
	}
	if (state->S_key == 1)
	{
		if (state->player_pos.y < state->parse.hmap)
		{
			state->player_pos.x += 0.5 * -sin(state->angle);
			state->player_pos.y += 0.5 * cos(state->angle);
		}
	}
}

int	ft_loop(t_state *state)
{
	if (state->D_key == 1 || state->A_key == 1)
		d_or_a_key(state);
	if (state->W_key == 1 || state->S_key == 1)
		w_or_s_key(state);
	if (state->right_key == 1)
	{
		state->angle += (5 * RAD);
		state->angle_temp += (5 * RAD);
	}
	if (state->left_key == 1)
	{
		state->angle -= (5 * RAD);
		state->angle_temp -= (5 * RAD);
	}
	if (state->angle == (360 * RAD))
	{
		state->angle = 0;
		state->angle_temp = 0;
	}
	if (state->angle / RAD < 0)
	{
		state->angle += (360 * RAD);
		state->angle_temp += (360 * RAD);
	}
	distance_dividend_wall(state->player_pos, state->y_plane, state->parse.lenmax);
	distance_dividend_wall(state->player_pos, state->x_plane, state->parse.hmap);
	ft_planes_sprites(state);
	distance_dividend_sprites(state);
	ft_intersections(state);
	return (0);
}
