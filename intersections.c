#include "cub3d.h"

void	ft_planes(t_state *state)
{
	int	i;

	i = -1;
	state->x_plane = malloc(mapHeight * (sizeof(t_plane)));
	state->y_plane = malloc(mapWidth * (sizeof(t_plane)));
	while (++i < mapHeight)
	{
		state->x_plane[i].a = 0;
		state->x_plane[i].b = 1;
		state->x_plane[i].c = 0;
		state->x_plane[i].d = -i;
	}
	i = -1;
	while (++i < mapWidth)
	{
		state->y_plane[i].a = 1;
		state->y_plane[i].b = 0;
		state->y_plane[i].c = 0;
		state->y_plane[i].d = -i;
	}
}

void	ft_ray_dir(t_state *state)
{
	double	r_h;
	double	r_v;
	int		i;
	int		j;

	j = 0;
	r_h = (2 * tan((60 * M_PI / 180) / 2)) / screenWidth;
	r_v = (r_h * screenHeight) / screenWidth;
	state->dir_ray = malloc(screenHeight * sizeof(t_vector *));
	while (j < screenHeight)
	{
		state->dir_ray[j] = malloc(screenWidth * sizeof(t_vector));
		i = 0;
		while (i < screenWidth)
		{
			state->dir_ray[j][i].x = (i - (screenWidth * 0.5)) * r_h;
			state->dir_ray[j][i].y = -1;
			state->dir_ray[j][i].z = -(j - (screenHeight * 0.5)) * r_v;
			i++;
		}
		j++;
	}
}

void	ft_intersections(t_state *state)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < screenHeight)
	{
		i = 0;
		while (i < screenWidth)
		{
			if (state->angle_temp)
			{
				state->dir_ray[j][i] = rotate_vector_z(state->dir_ray[j][i], \
				(state->angle_temp * (M_PI / 180)));
			}
			ft_print_the_right_pixel(state, i, j);
			i++;
		}
		j++;
	}
	state->angle_temp = 0;
	mlx_put_image_to_window(state->mlx, state->win, state->img, 0, 0);
}

double	ft_distance(t_state *state, t_plane plane, t_vector dir)
{
	double	t;
	double	divisor;

	divisor = ((plane.a * dir.x) + (plane.b * dir.y));
	if (divisor == 0)
		return (-1);
	t = -(((plane.a * state->player_pos.x) \
	+ (plane.b * state->player_pos.y) + plane.d) / divisor);
	if (t < 0)
		return (-1);
	return (t);
}

t_inter	ft_get_coord(t_vector dir, t_state *state, int i, int j)
{
	double	t;
	t_inter	inter;

	t = ft_distance(state, state->plane[state->i_plane], dir);
	inter.t = t;
	if (t == -1)
		return (inter);
	inter.coord.x = state->player_pos.x + (t * dir.x);
	inter.coord.y = state->player_pos.y + (t * dir.y);
	inter.coord.z = state->player_pos.z + (t * dir.z);
	inter.coord = rectif_pos(state, state->plane[state->i_plane], inter.coord);
	if (inter.coord.z < 0)
		my_mlx_pixel_put(state, i, j, 0x00FF00);
	else if (inter.coord.z > 1)
		my_mlx_pixel_put(state, i, j, 0x0000FF);
	else if (inter.coord.z >= 0 && inter.coord.z <= 1)
		return (inter);
	inter.t = -1;
	return (inter);
}
