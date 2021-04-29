/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectif_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:59:59 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 09:00:02 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_fmax(double a, double b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

double	ft_fmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

t_coord	rectif_pos(t_state *state, t_plane plane, t_coord inter)
{
	if (ft_fmax(inter.y, fabs(plane.d))
		- ft_fmin(inter.y, fabs(plane.d)) <= 0.0001)
	{
		if (state->player_pos.y < inter.y)
			inter.y = fabs(plane.d);
		else
			inter.y = fabs(plane.d) - 1;
	}
	else if (ft_fmax(inter.x, fabs(plane.d))
		- ft_fmin(inter.x, fabs(plane.d)) <= 0.0001)
	{
		if (state->player_pos.x < inter.x)
			inter.x = fabs(plane.d);
		else
			inter.x = fabs(plane.d) - 1;
	}
	return (inter);
}
