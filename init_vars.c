/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:59:06 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:59:07 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_init(t_state *state)
{
	state->scale = 2;
	state->W_key = 0;
	state->D_key = 0;
	state->S_key = 0;
	state->A_key = 0;
	state->left_key = 0;
	state->right_key = 0;
	state->z_angle = 0;
	state->up_key = 0;
	state->down_key = 0;
	state->c_key = 0;
	state->space_key = 0;
}

int	ft_init_game(t_state *state)
{
	key_init(state);
	state->r_h = (2 * tan((60 * RAD) / 2)) / state->parse.Rx;
	state->player_pos.x = (double)state->parse.xplayer + 0.5;
	state->player_pos.y = (double)state->parse.yplayer + 0.5;
	state->player_pos.z = 0.5;
	state->mlx = mlx_init();
	if (state->mlx == NULL)
		return (0);
	state->win = mlx_new_window(state->mlx, state->parse.Rx,
			state->parse.Ry, "cub3d");
	state->img1 = mlx_new_image(state->mlx, state->parse.Rx, state->parse.Ry);
	state->img2 = mlx_new_image(state->mlx, state->parse.Rx, state->parse.Ry);
	state->addr1 = mlx_get_data_addr(state->img1, &state->bits_per_pixel,
			&state->line_length, &state->endian);
	state->addr2 = mlx_get_data_addr(state->img2, &state->bits_per_pixel,
			&state->line_length, &state->endian);
	state->text = malloc (5 * sizeof(t_textures));
	return (state->win != NULL || state->text != NULL);
}
