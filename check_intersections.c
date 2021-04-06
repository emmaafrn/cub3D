#include "cub3d.h"

double	check_north(t_state *state, int i, int j)
{
	int		l;
	double	t;

	t = -1;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l >= 0 && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		if (t >= 0)
		{
			if ((int)state->interr.inter.x >= 0 && (int)state->interr.inter.x < mapWidth
			&& ((int)state->interr.inter.y >= 0 && (int)state->interr.inter.y < mapHeight)
			&& worldMap[(int)state->interr.inter.y][(int)state->interr.inter.x] == 1)
				return (t);
			else
				t = -1;
		}
		l--;
	}
	return (t);
}

double	check_south(t_state *state, int i, int j)
{
	int		l;
	double	t;

	t = -1;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l < mapHeight && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		if (t >= 0)
		{
			if (((int)state->interr.inter.x >= 0 && (int)state->interr.inter.x < mapWidth)
			&& ((int)state->interr.inter.y >= 0 && (int)state->interr.inter.y < mapHeight)
			&& worldMap[(int)state->interr.inter.y][(int)state->interr.inter.x] == 1)
				return (t);
			else
				t = -1;
		}
		l++;
	}
	return (t);
}

double	check_east(t_state *state, int i, int j)
{
	int		l;
	double	t;

	t = -1;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l < mapWidth && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		if (t >= 0)
		{
			if (((int)state->interr.inter.x >= 0 && (int)state->interr.inter.x < mapWidth)
			&& ((int)state->interr.inter.y >= 0 && (int)state->interr.inter.y < mapHeight)
			&& worldMap[(int)state->interr.inter.y][(int)state->interr.inter.x] == 1)
				return (t);
			else
				t = -1;
		}
		l++;
	}
	return (t);
}

double	check_west(t_state *state, int i, int j)
{
	int		l;
	double	t;

	t = -1;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l >= 0 && t < 0)
	{
		state->i_plane = l;
		t = ft_lol(state->dir_ray[j][i], state, i, j);
		if (t >= 0)
		{
			if (((int)state->interr.inter.x >= 0 && (int)state->interr.inter.x < mapWidth)
			&& ((int)state->interr.inter.y >= 0 && (int)state->interr.inter.y < mapHeight)
			&& worldMap[(int)state->interr.inter.y][(int)state->interr.inter.x] == 1)
				return (t);
			else
				t = -1;
		}
		l--;
	}
	return (t);
}
