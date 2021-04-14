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
	{1,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,2,0,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void		my_mlx_pixel_put(t_state *state, int x, int y, int color)
{
	char	*dst;

	dst = state->addr + (y * state->line_length + x * (state->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


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

void	ft_orientation(t_state *state, int i, int j)
{
	int		result;
	double	ratioSx;
	double	decimal;
	int		imgx;
	int		imgy;
	int		sprite_num;
	int		color;
	int		p = 0;

	state->wall_text = ft_find_texture(state, i, j);
	result = state->wall_text.result;
	sprite_num = -1;
	while (sprite_num != -2 && sprite_num < state->nb_sprites && p == 0)
	{
		sprite_num = ft_find_sprite(state->dir_ray[j][i], state, i, j, sprite_num + 1);
		if (sprite_num != -2 && (result == 5 || state->sprite_tab[sprite_num].inter.t < state->wall_text.t))
		{
			ratioSx = 1 - get_sprite_text(state, state->sprite_tab[sprite_num].inter.coord, sprite_num);
			imgx = (state->text[4].width - 1) * ratioSx;
			imgy = (state->text[4].height - 1) * state->sprite_tab[sprite_num].inter.coord.z;
			if (ratioSx >= 0 && ratioSx < 1)
			{
				color = *(unsigned int*)get_pixel(&state->text[4], imgx, imgy);
				if (color > 0xFF)
				{
					my_mlx_pixel_put(state, i, j, color);
					p = 1;
				}
			}
		}
	}
	if (p == 0 && (result == 1 || result == 2))
	{
		decimal = state->inter2_wall.y - (double)(long int)state->inter2_wall.y;
		if (result == 2)
			decimal = 1 - decimal;
		imgx = (state->text[result].width - 1) * decimal;
		imgy = (state->text[result].height - 1) * state->inter2_wall.z;
		my_mlx_pixel_put(state, i, j, *(unsigned int*)get_pixel(&state->text[result], imgx, imgy));
	}
	else if (p == 0 && (result == 0 || result == 3))
	{
		decimal = state->inter1_wall.x - (double)(long int)state->inter1_wall.x;
		if (result == 3)
			decimal = 1 - decimal;
		imgx = (state->text[result].width - 1) * decimal;
		imgy = (state->text[result].height - 1) * state->inter1_wall.z;
		my_mlx_pixel_put(state, i, j, *(unsigned int*)get_pixel(&state->text[result], imgx, imgy));
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
			state->dir_ray[j][i] = rotate_vector_z(state->dir_ray[j][i], (state->angle * (M_PI / 180)));
			ft_orientation(state, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(state->mlx, state->win, state->img, 0, 0);
}

double		ft_distance(t_state *state, t_plane plane, t_vector dir)
{
	double	t;
	double	divisor;

	divisor = ((plane.a * dir.x) + (plane.b * dir.y));
	if (divisor == 0)
		return (-1);
	t = -(((plane.a * state->player_pos.x) + (plane.b * state->player_pos.y) + plane.d) / divisor);
	if (t < 0)
		return (-1);
	return (t);
}

t_inter		ft_get_coord(t_vector dir, t_state *state, int i, int j)
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

int		ft_init_game(t_state *state)
{
	state->mlx = mlx_init();
	if (state->mlx == NULL)
		return (0);
	state->win = mlx_new_window(state->mlx, screenWidth, screenHeight, "cub3d");
	state->img = mlx_new_image(state->mlx, screenWidth, screenHeight);
	state->addr = mlx_get_data_addr(state->img, &state->bits_per_pixel, &state->line_length, &state->endian);
	state->text = malloc (5 * sizeof(t_textures));
	return (state->win != NULL || state->text != NULL);
}

int		main()
{
	t_state		state;

	state.player_pos.x = 5.5;
	state.player_pos.y = 6.5;
	state.player_pos.z = 0.5;
	state.inter1_wall.x = -1;
	state.inter1_wall.y = -1;
	state.inter1_wall.z = -1;
	state.inter2_wall.x = -1;
	state.inter2_wall.y = -1;
	state.inter2_wall.z = -1;
	state.k = 0;
	ft_planes(&state);
	if (!(ft_init_game(&state)))
		return (-1);
	mlx_get_texture(&state);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
