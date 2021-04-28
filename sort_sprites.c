/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 09:00:11 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 09:00:13 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_smaller_dist(t_state *state, int i, int j, double dist_min)
{
	t_sprite	temp;
	t_vector	v;
	double		dist;

	dist = INT_MAX;
	while (dist >= dist_min && j > i)
	{
		v.x = (state->sprite_tab[j].coord.x + 0.5) - state->player_pos.x;
		v.y = (state->sprite_tab[j].coord.y + 0.5) - state->player_pos.y;
		v.z = 0;
		dist = get_vector_norm(v);
		if (dist < dist_min)
		{
			temp = state->sprite_tab[i];
			state->sprite_tab[i] = state->sprite_tab[j];
			state->sprite_tab[j] = temp;
			dist_min = dist;
		}
		j--;
	}
}

void	ft_sort_sprites(t_state *state)
{
	double		dist_min;
	t_vector	v;
	int			i;
	int			j;

	i = 0;
	while (i < state->nb_sprites)
	{
		v.x = (state->sprite_tab[i].coord.x + 0.5) - state->player_pos.x;
		v.y = (state->sprite_tab[i].coord.y + 0.5) - state->player_pos.y;
		v.z = 0;
		dist_min = get_vector_norm(v);
		j = state->nb_sprites - 1;
		ft_smaller_dist(state, i, j, dist_min);
		i++;
	}
}
