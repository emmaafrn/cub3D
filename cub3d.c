/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:13:40 by efarin            #+#    #+#             */
/*   Updated: 2021/03/26 11:13:44 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	worldMap[mapHeight][mapWidth]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	ft_planes(t_state *state)
{
	int	i;

	i = -1;
	state->x_plane = malloc(mapHeight * (sizeof(t_plane)));
	state->y_plane = malloc(mapWidth * (sizeof(t_plane)));
	printf("width = %d", mapWidth);
	printf("Height = %d", mapHeight);
	while (++i < mapHeight)
	{
		state->x_plane[i].a = 0;
		state->x_plane[i].b = 1;
		state->x_plane[i].c = 0;
		state->x_plane[i].d = i;
		printf("xplane = %f||%f||%f||%f\n", state->x_plane[i].a, state->x_plane[i].b, state->x_plane[i].c, state->x_plane[i].d);
	}
	i = -1;
	while (++i < mapWidth)
	{
		state->y_plane[i].a = 0;
		state->y_plane[i].b = 1;
		state->y_plane[i].c = 0;
		state->y_plane[i].d = i;
		printf("yplane = %f||%f||%f||%f\n", state->y_plane[i].a, state->y_plane[i].b, state->y_plane[i].c, state->y_plane[i].d);
	}
}

void	ft_ray_dir(t_state *state)
{
	float	r_h;
	float	r_v;
	int		i;
	int		j;

	j = 0;
	r_h = (2 * tan((60 * M_PI / 180) / 2))/screenWidth;
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
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (j < screenHeight)
	{
		i = 0;
		while (i < screenWidth)
		{
			state->dir_ray[j][i] = rotate_vector_z(state->dir_ray[j][i], state->angle);
			state->interr.t = INT_MAX;
			// if (state->angle >= 0 && state->angle < 90)
			// {
			// 	check_north(state, i, j);
			// 	check_east(state, i, j);
			// 	mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x000000);
			// }
			// if (state->angle >= 90 && state->angle < 180)
			// {
			// 	check_east(state, i, j);
			// 	check_south(state, i, j);
			// 	mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x000000);
			// }
			// if (state->angle >= 180 && state->angle < 270)
			// {
			// 	check_south(state, i, j);
			// 	check_west(state, i, j);
			// 	mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x000000);
			// }
			// if (state->angle >= 270 && state->angle < 360)
			// {
			// 	check_north(state, i, j);
			// 	check_west(state, i, j);
			// 	mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x000000);
			// }
			check_north(state, i, j);
			check_east(state, i, j);
			check_south(state, i, j);
			check_west(state, i, j);
			i++;
		}
		j++;
	}
}

float		ft_distance(t_state *state, t_plane plane, t_vector dir)
{
	float	t;
	float	divisor;

	divisor = ((plane.a * dir.x) + (plane.b * dir.y));
	if (divisor == 0)
		return (0);
	t = -(((plane.a * state->player_pos.x) + (plane.b * state->player_pos.y) - plane.d) / divisor);
	if (t < 0)
		return (0);
	return (t);
}

void	ft_lol(t_vector dir, t_state *state, int i, int j)
{
	float	t;
	t_coord	inter;
	
	t = ft_distance(state, state->plane[state->i_plane], dir);
	if (t == 0)
		return ;
	inter.x = state->player_pos.x + (t * dir.x);
	inter.y = state->player_pos.y + (t * dir.y);
	inter.z = state->player_pos.z + (t * dir.z);
	inter = rectif_pos(state, state->plane[state->i_plane], inter);
	if (t < state->interr.t && inter.z > 0 && inter.z < 1)
		if (((int)inter.x >=0 && (int)inter.x < mapWidth) && ((int)inter.y >=0 && (int)inter.y < mapHeight) && worldMap[(int)inter.y][(int)inter.x] == 1)
		{
			state->k = 1;
			state->interr.t = t;
			state->interr.inter.x = inter.x;
			state->interr.inter.y = inter.y;
			state->interr.inter.z = inter.z;
			state->interr.i = i;
			state->interr.j = j;
			mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x00FF00);
		}
	// printf("x = %d\n y = %d\n", (int)inter.x, (int)inter.y);
	// printf("y = %d\n", (int)inter.y);
	if (inter.z < 0)
		mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0xFF0000);
	if (inter.z > 1)
		mlx_pixel_put(&state->img, state->win, state->interr.i, state->interr.j, 0x0000FF);
	
}

void	ft_loop(t_state *state)
{
	ft_ray_dir(state);
	ft_intersections(state);
	mlx_clear_window(state->mlx, state->win);
}

int		ft_init_game(t_state *state)
{
	state->mlx = mlx_init();
	if (state->mlx == NULL)
		return (0);
	mlx_loop_hook(state->mlx, ft_loop, state);
	state->win = mlx_new_window(state->mlx, screenWidth, screenHeight, "cub3d");
	state->img = mlx_new_image(state->mlx, screenWidth, screenHeight);
	state->addr = mlx_get_data_addr(state->img, &state->bits_per_pixel, &state->line_length, &state->endian);
	return (state->win != NULL);
}

int		key_hook(int keycode, t_state *state)
{
	printf("keycode = %d\n", keycode);
	printf("posX = %f\n", state->player_pos.x);
	printf("angle = %f\n", state->angle);
	if (keycode == KEY_D)
		if (state->player_pos.x > 0 && state->player_pos.x < screenWidth)
			state->player_pos.x += 0.5;
	if (keycode == KEY_A)
		if (state->player_pos.x > 0 && state->player_pos.x < screenWidth)
			state->player_pos.x -= 0.5;
	if (keycode == KEY_W)
		if (state->player_pos.y > 0 && state->player_pos.y < screenHeight)
			state->player_pos.y -= 0.5;
	if (keycode == KEY_S)
		if (state->player_pos.y > 0 && state->player_pos.y < screenHeight)
			state->player_pos.y += 0.5;
	if (keycode == KEY_RIGHT)
		state->angle += 0.5;
	if (keycode == KEY_LEFT)
		state->angle -= 0.5;
	if (state->angle == 360 * (M_PI / 180))
		state->angle = 0;
	if (keycode == KEY_ESC)
		exit(0);
}

int		main()
{
	t_state		state;

	state.player_pos.x = 2;
	state.player_pos.y = 6.0;
	state.player_pos.z = 0.5;
	state.k = 0;
	state.interr.t = INT_MAX;
	ft_planes(&state);
	if (!(ft_init_game(&state)))
		return (-1);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_key_hook(state.win, key_hook, &state);
	mlx_loop(state.mlx);
}
