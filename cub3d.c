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
	{1,1,0,0,0,2,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void		my_mlx_pixel_put(t_state *state, int x, int y, int color)
{
	char	*dst;

	if ((color >> 24) == 0xFF)
		return ;
	dst = state->addr + (y * state->line_length + x * (state->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

char		*get_pixel(t_textures *text, int x, int y)
{
	char	*dst;
	dst = text->addr + ((text->height - y - 1) * text->line_length + x * (text->bits_per_pixel / 8));
	return (dst);
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

int	ft_texture(double t1, double t2, int text1, int text2)
{
	if (t1 == -1 && t2 == -1)
		return (5);
	if (t2 == -1)
		return (text1);
	if (t1 == -1)
		return (text2);
	if (t1 < t2)
		return (text1);
	else
		return (text2);
}

void	ft_orientation(t_state *state, int i, int j)
{
	double	t1;
	double	t2;
	int		text1;
	int		text2;
	int		result;
	double	decimal;
	int		imgx;
	int		imgy;
	int		k;
	int		color;
	int		p = 0;

	t2 = -1;
	if (state->dir_ray[j][i].y <= 0 && !(text1 = 0))
	{
		t1 = check_north(state, i, j);
		if (state->dir_ray[j][i].x >= 0 && (text2 = 1))
			t2 = check_east(state, i, j);
		else if (state->dir_ray[j][i].x <= 0 && (text2 = 2))
			t2 = check_west(state, i, j);
	}
	else
	{
		t1 = check_south(state, i, j);
		text1 = 3;
		if (state->dir_ray[j][i].x >= 0 && (text2 = 1))
			t2 = check_east(state, i, j);
		else if (state->dir_ray[j][i].x <= 0 && (text2 = 2))
			t2 = check_west(state, i, j);
	}
	result = ft_texture(t1, t2, text1, text2);
	k = ft_find_sprite(state->dir_ray[j][i], state, i, j);
	if (k != -1 && ((result == text1 && state->sprite_tab[k].inter.t < t1)
	|| (result == text2 && state->sprite_tab[k].inter.t < t2) || result == 5))
	{
		decimal = state->sprite_tab[k].inter.coord.x - (double)(long int)state->sprite_tab[k].inter.coord.x;
		imgx = (state->text[4].width - 1) * decimal;
		imgy = (state->text[4].height - 1) * state->sprite_tab[k].inter.coord.z;
		color = *(unsigned int*)get_pixel(&state->text[4], imgx, imgy);
		// printf("color = %d\n", color);
		if (color > 0xFF)
		{
			my_mlx_pixel_put(state, i, j, color);
			p = 1;
		}
	}
	if (p == 0 && result == text2)
	{
		decimal = state->inter2_wall.y - (double)(long int)state->inter2_wall.y;
		if (result == 2)
			decimal = 1 - decimal;
		imgx = (state->text[result].width - 1) * decimal;
		imgy = (state->text[result].height - 1) * state->inter2_wall.z;
		my_mlx_pixel_put(state, i, j, *(unsigned int*)get_pixel(&state->text[result], imgx, imgy));
	}
	else if (p == 0 && result == text1)
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
	// state->player_dir = rotate_vector_z(state->player_dir, (state->angle * (M_PI / 180)));
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

t_inter		ft_lol(t_vector dir, t_state *state, int i, int j)
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

int	ft_loop(t_state *state, int keycode)
{
	if (state->D_key == 1)
		if (state->player_pos.x < mapWidth)
			{
				state->player_pos.x += 0.5 * cos(state->angle * (M_PI / 180));
				state->player_pos.y += 0.5 * sin(state->angle * (M_PI / 180));
			}
	if (state->A_key == 1)
		if (state->player_pos.x > 0)
		{
			state->player_pos.x += -0.5 * cos(state->angle * (M_PI / 180));
			state->player_pos.y += -0.5 * sin(state->angle * (M_PI / 180));
		}
	if (state->W_key == 1)
		if (state->player_pos.y > 0)
		{
			state->player_pos.x += -0.5 * -sin(state->angle * (M_PI / 180));
			state->player_pos.y += -0.5 * cos(state->angle * (M_PI / 180));
		}
	if (state->S_key == 1)
		if (state->player_pos.y < mapHeight)
		{
			state->player_pos.x += 0.5 * -sin(state->angle * (M_PI / 180));
			state->player_pos.y += 0.5 * cos(state->angle * (M_PI / 180));
		}
	if (state->right_key == 1)
		state->angle += 5;
	if (state->left_key == 1)
		state->angle -= 5;
	if (state->angle == 360)
		state->angle = 0;
	if (state->angle < 0)
		state->angle += 360;
	ft_ray_dir(state);
	ft_planes_sprites(state);
	ft_intersections(state);
	//mlx_clear_window(state->mlx, state->win);
	return (0);
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

int		key_hook(int keycode, t_state *state)
{
// 	printf("keycode = %d\n", keycode);
// 	printf("posX = %f\n", state->player_pos.x);
// 	printf("angle = %f\n", state->angle);
	if (keycode == KEY_D)
		state->D_key = 1;
	if (keycode == KEY_A)
		state->A_key = 1;
	if (keycode == KEY_W)
		state->W_key = 1;
	if (keycode == KEY_S)
		state->S_key = 1;
	if (keycode == KEY_RIGHT)
		state->right_key = 1;
	if (keycode == KEY_LEFT)
		state->left_key = 1;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int		release_key(int keycode, t_state *state)
{
	// printf("keycode = %d\n", keycode);
	// printf("posX = %f\n", state->player_pos.x);
	// printf("angle = %f\n", state->angle);
	if (keycode == KEY_D)
		state->D_key = 0;
	if (keycode == KEY_A)
		state->A_key = 0;
	if (keycode == KEY_W)
		state->W_key = 0;
	if (keycode == KEY_S)
		state->S_key = 0;
	if (keycode == KEY_RIGHT)
		state->right_key = 0;
	if (keycode == KEY_LEFT)
		state->left_key = 0;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int		main()
{
	t_state		state;

	state.player_pos.x = 5.5;
	state.player_pos.y = 6.5;
	state.player_pos.z = 0.5;
	// state.player_dir.x = 0;
	// state.player_dir.y = -1;
	// state.player_dir.z = 0;
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
	state.text[0].img = mlx_png_file_to_image(state.mlx, "./mossy.png", &state.text[0].width, &state.text[0].height);
	state.text[0].addr = mlx_get_data_addr(state.text[0].img, &state.text[0].bits_per_pixel, &state.text[0].line_length, &state.text[0].endian);
	state.text[1].img = mlx_png_file_to_image(state.mlx, "./greystone.png", &state.text[1].width, &state.text[1].height);
	state.text[1].addr = mlx_get_data_addr(state.text[1].img, &state.text[1].bits_per_pixel, &state.text[1].line_length, &state.text[1].endian);
	state.text[2].img = mlx_png_file_to_image(state.mlx, "./redbrick.png", &state.text[2].width, &state.text[2].height);
	state.text[2].addr = mlx_get_data_addr(state.text[2].img, &state.text[2].bits_per_pixel, &state.text[2].line_length, &state.text[2].endian);
	state.text[3].img =mlx_png_file_to_image(state.mlx, "./purplestone.png", &state.text[3].width, &state.text[3].height);
	state.text[3].addr = mlx_get_data_addr(state.text[3].img, &state.text[3].bits_per_pixel, &state.text[3].line_length, &state.text[3].endian);
	state.text[4].img =mlx_xpm_file_to_image(state.mlx, "./sprite.xpm", &state.text[4].width, &state.text[4].height);
	state.text[4].addr = mlx_get_data_addr(state.text[4].img, &state.text[4].bits_per_pixel, &state.text[4].line_length, &state.text[4].endian);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
