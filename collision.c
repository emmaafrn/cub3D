#include "cub3d.h"

void	ft_collision(t_state *state)
{
	if (state->parse.map[(int)state->ply_temp.y][(int)state->player_pos.x] != '0')
		state->player_pos.x = state->ply_temp.x;
	else if (state->parse.map[(int)state->player_pos.y][(int)state->ply_temp.x] != '0')
		state->player_pos.y = state->ply_temp.y;
	else if (state->parse.map[(int)state->player_pos.y][(int)state->player_pos.x] != '0')
		state->player_pos = state->ply_temp;
	if ((int)state->player_pos.x >= state->parse.lenmax)
		state->player_pos = state->ply_temp;
	else if ((int)state->player_pos.x <= 0 || (int)state->player_pos.y <= 0)
		state->player_pos = state->ply_temp;
	else if ((int)state->player_pos.y >= state->parse.hmap)
		state->player_pos = state->ply_temp;
}
