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

int		ft_init_game(t_state *state)
{
	state->W_key = 0;
	state->D_key = 0;
	state->S_key = 0;
	state->A_key = 0;
	state->left_key = 0;
	state->right_key = 0;
	state->player_pos.x = state->parse.xplayer;
	state->player_pos.y = state->parse.yplayer;
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
		return (-1);
	}
	ft_planes(&state);
	ft_ray_dir(&state);
	if (!(ft_init_game(&state)))
	{
		printf("Erreur lors de la creation de la fenêtre !\n");
		free(state.dir_ray);
		return (-1);
	}
	if (!(mlx_get_texture(&state)))
	{
		printf("Erreur de récupération des textures !\n");
		free(state.dir_ray);
		return (-1);
	}
	ft_mem_sprite_tab(&state);
	ft_coord_sprites(&state);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
