/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:57:38 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:57:40 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline double	calc_dividend(t_plane plane, double rs, t_coord pos)
{
	rs = ((plane.a * pos.x) + (plane.b * pos.y) + plane.d);
	return (rs);
}

void	distance_dividend_wall(t_coord pos, t_plane *plane, int limit)
{
	double	rs;
	int		i;

	i = -1;
	while (++i < limit)
	{
		rs = calc_dividend(plane[i], rs, pos);
		plane[i].rs = rs;
	}
}

void	distance_dividend_sprites(t_state *state)
{
	double	rs;
	t_coord	pos;
	int		i;

	i = -1;
	pos = state->player_pos;
	while (++i < state->nb_sprites)
	{
		rs = calc_dividend(state->sprite_tab[i].plane, rs, pos);
		state->sprite_tab[i].plane.rs = rs;
	}
}
