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
#include "parsing/parsing.h"

void		get_hmap(t_state *state)
{
	int	i;

	i = 0;
	while (state->parse.map[i] != NULL)
		i++;
	state->parse.hmap = i;
}

void		my_mlx_pixel_put(t_state *state, int x, int y, int color)
{
	char	*dst;

	dst = state->addr + (y * state->line_length + x * (state->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_get_parse_infos(t_state *state)
{
	if (state->parse.position == 'W')
		state->angle = 270 * RAD;
	if (state->parse.position == 'E')
		state->angle = 90 * RAD;
	if (state->parse.position == 'S')
		state->angle = 180 * RAD;
}

void	ft_free_n_exit(t_state *state)
{
	ft_free(state->dir_ray, (state->parse.Rx * state->parse.Ry));
	free(state->y_plane);
	free(state->x_plane);
	if (state->sprite_tab)
		free(state->sprite_tab);
	exit(0);
}

int		ft_init_game(t_state *state)
{
	state->W_key = 0;
	state->D_key = 0;
	state->S_key = 0;
	state->A_key = 0;
	state->left_key = 0;
	state->right_key = 0;
	state->z_angle = 0;
	state->up_key = 0;
	state->down_key = 0;
	state->player_pos.x = (double)state->parse.xplayer + 0.5;
	state->player_pos.y = (double)state->parse.yplayer + 0.5;
	state->player_pos.z = 0.5;
	state->inter1_wall.x = -1;
	state->inter1_wall.y = -1;
	state->inter1_wall.z = -1;
	state->inter2_wall.x = -1;
	state->inter2_wall.y = -1;
	state->inter2_wall.z = -1;
	state->mlx = mlx_init();
	if (state->mlx == NULL)
		return (0);
	state->win = mlx_new_window(state->mlx, state->parse.Rx, state->parse.Ry, "cub3d");
	state->img = mlx_new_image(state->mlx, state->parse.Rx, state->parse.Ry);
	state->addr = mlx_get_data_addr(state->img, &state->bits_per_pixel, &state->line_length, &state->endian);
	state->text = malloc (5 * sizeof(t_textures));
	return (state->win != NULL || state->text != NULL);
}

int		main(int arc, char **arv)
{
	t_state		state;

	state.parse = *ismapvalid(arv);
	get_hmap(&state);
	if (!state.parse.map)
	{
		printf("Mauvaise map, réessayes !\n");
		ft_free_n_exit(&state);
	}
	ft_ray_dir(&state);
	if (!ft_planes(&state) || !(ft_init_game(&state)))
		ft_free_n_exit(&state);
	if (!(mlx_get_texture(&state)))
	{
		printf("Erreur de récupération des textures !\n");
		ft_free_n_exit(&state);
	}
	ft_get_parse_infos(&state);
	ft_mem_sprite_tab(&state);
	ft_coord_sprites(&state);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
