/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:59:37 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:59:39 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_get_texture_first(t_state *state)
{
	state->text[0].img = mlx_png_file_to_image(state->mlx, state->parse.pathtoNO, \
	&state->text[0].width, &state->text[0].height);
	if (state->text[0].img == NULL)
	{
		printf("Error, text north\n");
		return (0);
	}
	state->text[0].addr = mlx_get_data_addr(state->text[0].img, &state->text[0].bits_per_pixel, \
	&state->text[0].line_length, &state->text[0].endian);
	state->text[1].img = mlx_png_file_to_image(state->mlx, state->parse.pathtoEA, \
	&state->text[1].width, &state->text[1].height);
	if (state->text[1].img == NULL)
	{
		printf("Error, text east\n");
		return (0);
	}
	state->text[1].addr = mlx_get_data_addr(state->text[1].img, &state->text[1].bits_per_pixel, \
	&state->text[1].line_length, &state->text[1].endian);
	return (1);
}

int	mlx_get_texture_scnd(t_state *state)
{
	state->text[2].img = mlx_png_file_to_image(state->mlx, state->parse.pathtoWE, \
	&state->text[2].width, &state->text[2].height);
	if (state->text[2].img == NULL)
	{
		printf("Error, text west\n");
		return (0);
	}
	state->text[2].addr = mlx_get_data_addr(state->text[2].img, &state->text[2].bits_per_pixel, \
	&state->text[2].line_length, &state->text[2].endian);
	state->text[3].img = mlx_png_file_to_image(state->mlx, state->parse.pathtoSO, \
	&state->text[3].width, &state->text[3].height);
	if (state->text[3].img == NULL)
	{
		printf("Error, text south\n");
		return (0);
	}
	state->text[3].addr = mlx_get_data_addr(state->text[3].img, &state->text[3].bits_per_pixel, \
	&state->text[3].line_length, &state->text[3].endian);
	return (1);
}

int	mlx_get_texture(t_state *state)
{
	if (!mlx_get_texture_first(state) || !mlx_get_texture_scnd(state))
		return (0);
	state->text[4].img = mlx_xpm_file_to_image(state->mlx, state->parse.pathtoS, \
	&state->text[4].width, &state->text[4].height);
	if (state->text[4].img == NULL)
	{
		printf("Error, text sprites\n");
		return (0);
	}
	state->text[4].addr = mlx_get_data_addr(state->text[4].img, &state->text[4].bits_per_pixel, \
	&state->text[4].line_length, &state->text[4].endian);
	return (1);
}
