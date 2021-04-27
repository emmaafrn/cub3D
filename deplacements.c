#include "cub3d.h"

void	w_or_s_key(t_state *state)
{
	if (state->W_key == 1)
	{
		state->player_pos.x += -0.5 * -sin(state->angle);
		state->player_pos.y += -0.5 * cos(state->angle);
	}
	if (state->S_key == 1)
	{
		state->player_pos.x += 0.5 * -sin(state->angle);
		state->player_pos.y += 0.5 * cos(state->angle);
	}
}

void	up_or_down(t_state *state)
{
	if (state->up_key == 1 && state->z_angle > (-20 * RAD))
		state->z_angle -= (2 * RAD);
	if (state->down_key == 1 && state->z_angle < (20 * RAD))
		state->z_angle += (2 * RAD);
}

void	jump_or_squat(t_state *state)
{
	if (state->space_key == 1)
		state->player_pos.z = 1;
	if (state->space_key == 0 && state->player_pos.z == 1)
		state->player_pos.z = 0.5;
	if (state->c_key == 1)
		state->player_pos.z = 0;
	if (state->c_key == 0 && state->player_pos.z == 0)
		state->player_pos.z = 0.5;
}
