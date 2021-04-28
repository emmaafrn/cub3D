/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:33:14 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 11:33:16 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	scaling_pixel_color(int i, int j, t_thread *data, int scale)
{
	t_coord	pxl;

	pxl.y = j;
	while (pxl.y < (j + scale) && pxl.y < data->state->parse.Ry)
	{
		pxl.x = i;
		while (pxl.x < (i + scale) && pxl.x < data->state->parse.Rx)
		{
			my_mlx_pixel_put(data->state, pxl.x, pxl.y, data->pxl_color);
			pxl.x++;
		}
		pxl.y++;
	}
	return (pxl);
}
