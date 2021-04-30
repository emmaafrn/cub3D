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
	int	sizex;
	int	sizey;

	mlx_get_screen_size(state, &sizex, &sizey);
	if (state->parse.Rx > sizex)
		state->parse.Rx = sizex;
	if (state->parse.Ry > sizey)
		state->parse.Ry = sizey;
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

void	get_parse(t_struct *map, t_state *state, int arc, char **arv)
{
	check_arguments(state, arc, arv);
	map = ismapvalid(arv);
	if (!map)
	{
		printf("Map not valid, retry !\n");
		ft_free_n_exit(state);
	}
	state->parse = *map;
	get_hmap(state);
}

int	main(int arc, char **arv)
{
	t_state		state;
	t_struct	*map;

	map = NULL;
	get_parse(map, &state, arc, arv);
	ft_get_parse_infos(&state);
	if (!ft_planes(&state) || !ft_init_game(&state) || !mlx_get_texture(&state))
		ft_free_n_exit(&state);
	ft_ray_dir(&state);
	ft_mem_sprite_tab(&state);
	ft_coord_sprites(&state);
	if (!malloc_thread_data_stuff(&state))
		ft_free_n_exit(&state);
	mlx_hook(state.win, 2, 0, key_hook, &state);
	mlx_hook(state.win, 3, 0, release_key, &state);
	mlx_hook(state.win, 17, 0, ft_free_n_exit, &state);
	mlx_loop_hook(state.mlx, ft_loop, &state);
	mlx_loop(state.mlx);
}
