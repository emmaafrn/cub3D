#include "cub3d.h"

double	is_there_wall(t_coord *inter_wall, t_inter inter, t_state *state)
{
	if ((int)inter.coord.x >= 0 && (int)inter.coord.x < state->parse.lenmax
		&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < state->parse.hmap)
		&& state->parse.map[(int)inter.coord.y][(int)inter.coord.x] == '1')
	{
		inter_wall->x = inter.coord.x;
		inter_wall->y = inter.coord.y;
		inter_wall->z = inter.coord.z;
	}
	else
		inter.t = -1;
	return (inter.t);
}

double	check_north(t_state *state, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l >= 0 && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_get_coord(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&state->inter1_wall, inter, state);
			if (inter.t != -1)
				return (inter.t);
		}
		l--;
	}
	return (inter.t);
}

double	check_south(t_state *state, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	state->plane = state->x_plane;
	l = (int)state->player_pos.y;
	while (l < state->parse.hmap && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_get_coord(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&state->inter1_wall, inter, state);
			if (inter.t != -1)
				return (inter.t);
		}
		l++;
	}
	return (inter.t);
}

double	check_east(t_state *state, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l < state->parse.lenmax && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_get_coord(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&state->inter2_wall, inter, state);
			if (inter.t != -1)
				return (inter.t);
		}
		l++;
	}
	return (inter.t);
}

double	check_west(t_state *state, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	state->plane = state->y_plane;
	l = (int)state->player_pos.x;
	while (l >= 0 && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_get_coord(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&state->inter2_wall, inter, state);
			if (inter.t != -1)
				return (inter.t);
		}
		l--;
	}
	return (inter.t);
}
