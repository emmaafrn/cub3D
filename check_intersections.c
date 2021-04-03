#include "cub3d.h"

float	check_north(t_state *state, int i, int j)
{
	int		l;
	float	t;

	t = 0;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l >= 0 && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		l--;
	}
	return (t);
}

float	check_south(t_state *state, int i, int j)
{
	int		l;
	float	t;

	t = 0;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l < mapHeight && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		l++;
	}
	return (t);
}

float	check_east(t_state *state, int i, int j)
{
	int		l;
	float	t;

	t = 0;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l < mapWidth && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		l++;
	}
	return (t);
}

float	check_west(t_state *state, int i, int j)
{
	int		l;
	float	t;

	t = 0;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l >= 0 && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		l--;
	}
	return (t);
}
