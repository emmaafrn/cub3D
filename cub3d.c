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
	state->x_plane = malloc((mapWidth + 1) * (sizeof(t_plane)));
	state->y_plane = malloc((mapHeight + 1) * (sizeof(t_plane)));
	while (++i < mapHeight)
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
			if (state->angle >= 0 && state->angle < 90)
				check_north(state, i, j);
			ft_lol(state->dir_ray[j][i], state);
			i++;
		}
		j++;
	}
}

float		ft_distance(t_coord *pos, t_plane *plane)
{
	float	t;
	float	divisor;

	divisor = ((plane->a * dir.x) + (plane->b * dir.y));
	if (divisor == 0)
		return (0);
	t = -((plane->a * pos->x) + (plane->b * pos->y) + plane->d);
	t /= divisor;
	if (t < 0)
		return (0);
	return (t);
}

void	ft_lol(t_vector dir, t_state *state)
{
	double	t;
	t_coord	inter;

	t = ft_distance(state->player_pos, state->plane);
	if (t == 0)
		return ;
	inter.z = state->player_pos.z + (t * dir.z);
	if (z > 0 && z < 1 && (state->k = 1))
		mlx_pixel_put(&state->img, state->win, i, j, 0xFFFFFF);
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
	if (!(ft_init_game(&state)))
		return (-1);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_key_hook(state.win, key_hook, &state);
	mlx_loop(state.mlx);
}
