/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:57:58 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:58:00 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_collision(t_state *state)
{
	if ((int)state->player_pos.x >= state->parse.lenmax)
		state->player_pos = state->ply_temp;
	else if ((int)state->player_pos.x <= 0 || (int)state->player_pos.y <= 0)
		state->player_pos = state->ply_temp;
	else if ((int)state->player_pos.y >= state->parse.hmap)
		state->player_pos = state->ply_temp;
	if (state->parse.map[(int)state->ply_temp.y][(int)state->player_pos.x]
		== '1')
		state->player_pos.x = state->ply_temp.x;
	if (state->parse.map[(int)state->player_pos.y][(int)state->ply_temp.x]
		== '1')
		state->player_pos.y = state->ply_temp.y;
	if (state->parse.map[(int)state->player_pos.y][(int)state->player_pos.x]
		== '1')
		state->player_pos = state->ply_temp;
}
