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

#define mapWidth 24
#define mapHeight 8
#define screenWidth 1024
#define screenHeight 512

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
	state->x_plane = malloc((mapWidth + 1) * (sizeof(t_planes)));
	state->y_plane = malloc((mapHeight + 1) * (sizeof(t_planes)));
	while (++i < mapWidth)
	{
		state->x_plane[i].a = 0;
		state->x_plane[i].b = 1;
		state->x_plane[i].c = 0;
		state->x_plane[i].d = i;
	}
	i = -1;
	while (++i < mapWidth)
	{
		state->y_plane[i].a = 0;
		state->y_plane[i].b = 1;
		state->y_plane[i].c = 0;
		state->y_plane[i].d = i;
	}
}

void	ft_ray_dir(t_state *state)
{
	double	r_h;
	double	r_v;
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
			ft_lol(i, j, state);
			i++;
		}
		j++;
	}
}

void	ft_lol(int i, int j, t_state *state)
{
	double	t;
	double	t2;
	double	z;
	double	z2;

	t = 0.0;
	t2 = 0.0;
	z = 0.0;
	z2 = 0.0;
	t = -((0 * state->player_pos.x) + (1 * state->player_pos.y)
	+ (0 * state->player_pos.z) - 1);
	t = t / ((0 * state->dir_ray[j][i].x) + (1 * state->dir_ray[j][i].y)
	+ (0 * state->dir_ray[j][i].z));
	z = state->player_pos.z + (t * state->dir_ray[j][i].z);
	t2 = -((1 * state->player_pos.x) + (0 * state->player_pos.y)
	+ (0 * state->player_pos.z) - 1);
	t2 = t2 / ((1 * state->dir_ray[j][i].x) + (0 * state->dir_ray[j][i].y)
	+ (0 * state->dir_ray[j][i].z));
	z2 = state->player_pos.z + (t2 * state->dir_ray[j][i].z);
	if (z > 0 && z < 1 && t > 0)
		mlx_pixel_put(&state->img, state->win, i, j, 0xFFFFFF);
	else if (z2 > 0 && z2 < 1 && t2 > 0)
		mlx_pixel_put(&state->img, state->win, i, j, 0xFFFFFF);
	else if (z < 0 && t > 0)
		mlx_pixel_put(&state->img, state->win, i, j, 0x00FF00);
	else if (z > 1 && t > 0)
		mlx_pixel_put(&state->img, state->win, i, j, 0x0000CC);
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
	if (keycode == KEY_ESC)
		exit(0);
}

int		main()
{
	t_state		state;

	state.player_pos.x = 2;
	state.player_pos.y = 10.0;
	state.player_pos.z = 0.5;
	if (!(ft_init_game(&state)))
		return (-1);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_key_hook(state.win, key_hook, &state);
	mlx_loop(state.mlx);
}
