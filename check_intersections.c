#include "cub3d.h"

void	check_north(t_state *state, int i, int j)
{
	int		l;

	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l >= 0 && state->k == 0)
	{
		state->i_plane = l;
		ft_lol(state->dir_ray[j][i], state, i, j);
		l--;
	}
	state->k = 0;
}

void	check_south(t_state *state, int i, int j)
{
	int		l;

	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l < mapHeight && state->k == 0)
	{
		state->i_plane = l;
		ft_lol(state->dir_ray[j][i], state, i, j);
		l++;
	}
	state->k = 0;
}

void	check_east(t_state *state, int i, int j)
{
	int		l;

	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l < mapWidth && state->k == 0)
	{
		state->i_plane = l;
		ft_lol(state->dir_ray[j][i], state, i, j);
		l++;
	}
	state->k = 0;
}

void	check_west(t_state *state, int i, int j)
{
	int		l;

	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l >= 0 && state->k == 0)
	{
		state->i_plane = l;
		ft_lol(state->dir_ray[j][i], state, i, j);
		l--;
	}
	state->k = 0;
}
