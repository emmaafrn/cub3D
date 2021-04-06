#include "cub3d.h"

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
		inter = ft_lol(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < mapWidth
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < mapHeight)
			&& worldMap[(int)inter.coord.y][(int)inter.coord.x] == 1)
			{
				state->inter1_wall.x = inter.coord.x;
				state->inter1_wall.y = inter.coord.y;
				state->inter1_wall.z = inter.coord.z;
				return (inter.t);
			}
			else
				inter.t = -1;
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
	while (l < mapHeight && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_lol(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < mapWidth
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < mapHeight)
			&& worldMap[(int)inter.coord.y][(int)inter.coord.x] == 1)
			{
				state->inter1_wall.x = inter.coord.x;
				state->inter1_wall.y = inter.coord.y;
				state->inter1_wall.z = inter.coord.z;
				return (inter.t);
			}
			else
				inter.t = -1;
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
	while (l < mapWidth && inter.t < 0)
	{
		state->i_plane = l;
		inter = ft_lol(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < mapWidth
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < mapHeight)
			&& worldMap[(int)inter.coord.y][(int)inter.coord.x] == 1)
			{
				state->inter2_wall.x = inter.coord.x;
				state->inter2_wall.y = inter.coord.y;
				state->inter2_wall.z = inter.coord.z;
				return (inter.t);
			}
			else
				inter.t = -1;
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
		inter = ft_lol(state->dir_ray[j][i], state, i, j);
		if (inter.t >= 0)
		{
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < mapWidth
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < mapHeight)
			&& worldMap[(int)inter.coord.y][(int)inter.coord.x] == 1)
			{
				state->inter2_wall.x = inter.coord.x;
				state->inter2_wall.y = inter.coord.y;
				state->inter2_wall.z = inter.coord.z;
				return (inter.t);
			}
			else
				inter.t = -1;
		}
		l--;
	}
	return (inter.t);
}
