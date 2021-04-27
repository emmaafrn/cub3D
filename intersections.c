#include "cub3d.h"

int	ft_planes(t_state *state)
{
	int	i;

	i = -1;
	state->x_plane = malloc(state->parse.hmap * (sizeof(t_plane)));
	state->y_plane = malloc(state->parse.lenmax * (sizeof(t_plane)));
	if (state->x_plane == 0 || state->y_plane == 0)
		return (0);
	while (++i < state->parse.hmap)
	{
		state->x_plane[i].a = 0;
		state->x_plane[i].b = 1;
		state->x_plane[i].c = 0;
		state->x_plane[i].d = -i;
	}
	i = -1;
	while (++i < state->parse.lenmax)
	{
		state->y_plane[i].a = 1;
		state->y_plane[i].b = 0;
		state->y_plane[i].c = 0;
		state->y_plane[i].d = -i;
	}
	return (1);
}

void	ft_ray_dir(t_state *state)
{
	double	r_h;
	double	r_v;
	int		i;
	int		j;

	j = 0;
	r_h = (2 * tan((60 * RAD) / 2)) / state->parse.Rx;
	r_v = (r_h * state->parse.Ry) / state->parse.Rx;
	state->dir_ray = malloc(state->parse.Ry * sizeof(t_vector *));
	while (j < state->parse.Ry)
	{
		state->dir_ray[j] = malloc(state->parse.Rx * sizeof(t_vector));
		i = 0;
		while (i < state->parse.Rx)
		{
			state->dir_ray[j][i].x = (i - (state->parse.Rx * 0.5)) * r_h;
			state->dir_ray[j][i].y = -1;
			state->dir_ray[j][i].z = -(j - (state->parse.Ry * 0.5)) * r_v;
			i++;
		}
		j++;
	}
}

void	ft_intersections(t_state *state, int scale)
{
	int		i;
	int		j;

	j = 0;
	while (j < state->parse.Ry)
	{
		i = 0;
		while (i < state->parse.Rx)
		{
			state->temp = state->dir_ray[j][i];
			state->temp = rotate_vector_x(state->temp, \
			state->z_angle);
			state->temp = rotate_vector_z(state->temp, \
			state->angle);
			ft_print_the_right_pixel(state, i, j);
			scaling_pixel_color(i, j, state, scale);
			i += scale;
		}
		j += scale;
	}
	mlx_put_image_to_window(state->mlx, state->win, state->img, 0, 0);
}

double	ft_distance(t_plane plane, t_vector dir)
{
	double	t;
	double	divisor;

	divisor = ((plane.a * dir.x) + (plane.b * dir.y));
	if (divisor == 0)
		return (-1);
	t = -(plane.rs / divisor);
	if (t < 0)
		return (-1);
	return (t);
}

t_inter	ft_get_coord(t_vector dir, t_state *state, int i, int j)
{
	double	t;
	t_inter	inter;

	t = ft_distance(state->plane[state->i_plane], dir);
	inter.t = t;
	if (t == -1)
		return (inter);
	inter.coord.x = state->player_pos.x + (t * dir.x);
	inter.coord.y = state->player_pos.y + (t * dir.y);
	inter.coord.z = state->player_pos.z + (t * dir.z);
	inter.coord = rectif_pos(state, state->plane[state->i_plane], inter.coord);
	if (inter.coord.z < 0 || inter.coord.z > 1)
	{
		if (inter.coord.z < 0)
			state->pxl_color = 0x00FF00;
		else
			state->pxl_color = 0x0000FF;
		my_mlx_pixel_put(state, i, j, state->pxl_color);
	}
	else if (inter.coord.z >= 0 && inter.coord.z <= 1)
		return (inter);
	inter.t = -1;
	return (inter);
}
