/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:57:49 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:57:51 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

double	check_north(t_thread *data, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	data->plane = data->state->x_plane;
	l = (int)data->state->player_pos.y;
	while (l >= 0 && inter.t < 0)
	{
		data->i_plane = l;
		inter = ft_get_coord(data->temp, data, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&data->inter1_wall, inter, data->state);
			if (inter.t != -1)
				return (inter.t);
		}
		l--;
	}
	return (inter.t);
}

double	check_south(t_thread *data, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	data->plane = data->state->x_plane;
	l = (int)data->state->player_pos.y;
	while (l < data->state->parse.hmap && inter.t < 0)
	{
		data->i_plane = l;
		inter = ft_get_coord(data->temp, data, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&data->inter1_wall, inter, data->state);
			if (inter.t != -1)
				return (inter.t);
		}
		l++;
	}
	return (inter.t);
}

double	check_east(t_thread *data, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	data->plane = data->state->y_plane;
	l = (int)data->state->player_pos.x;
	while (l < data->state->parse.lenmax && inter.t < 0)
	{
		data->i_plane = l;
		inter = ft_get_coord(data->temp, data, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&data->inter2_wall, inter, data->state);
			if (inter.t != -1)
				return (inter.t);
		}
		l++;
	}
	return (inter.t);
}

double	check_west(t_thread *data, int i, int j)
{
	int		l;
	t_inter	inter;

	inter.t = -1;
	data->plane = data->state->y_plane;
	l = (int)data->state->player_pos.x;
	while (l >= 0 && inter.t < 0)
	{
		data->i_plane = l;
		inter = ft_get_coord(data->temp, data, i, j);
		if (inter.t >= 0)
		{
			inter.t = is_there_wall(&data->inter2_wall, inter, data->state);
			if (inter.t != -1)
				return (inter.t);
		}
		l--;
	}
	return (inter.t);
}
