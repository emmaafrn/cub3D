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

void	get_hmap(t_state *state)
{
	int	i;

	i = 0;
	while (state->parse.map[i] != NULL)
		i++;
	state->parse.hmap = i;
}

void	my_mlx_pixel_put(t_state *state, int x, int y, int color)
{
	char	*dst;

	dst = state->addr + (y * state->line_length
			+ x * (state->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_get_parse_infos(t_state *state)
{
	state->f_color = (state->parse.F_R << 16) + (state->parse.F_G << 8)
		+ (state->parse.F_B);
	state->c_color = (state->parse.C_R << 16) + (state->parse.C_G << 8)
		+ (state->parse.C_B);
	if (state->parse.position == 'W')
		state->angle = 270 * RAD;
	if (state->parse.position == 'E')
		state->angle = 90 * RAD;
	if (state->parse.position == 'S')
		state->angle = 180 * RAD;
}

int	main(int arc, char **arv)
{
	t_state		state;
	t_struct	*map;

	map = NULL;
	if (arc == 1)
	{
		printf("Erreur, pas d'argument(s)");	
		exit(0);
	}
	map = ismapvalid(arv);
	if (!map)
	{
		printf("Mauvaise map, réessayes !\n");
		ft_free_n_exit(&state);
	}
	state.parse = *map;
	get_hmap(&state);
	if (!ft_planes(&state) || !(ft_init_game(&state)))
		ft_free_n_exit(&state);
	if (!(mlx_get_texture(&state)))
	{
		printf("Erreur de récupération des textures !\n");
		ft_free_n_exit(&state);
	}
	ft_ray_dir(&state);
	ft_get_parse_infos(&state);
	ft_mem_sprite_tab(&state);
	ft_coord_sprites(&state);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_hook(state.win, 17, 0, ft_free_n_exit, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
