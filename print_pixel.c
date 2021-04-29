/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:59:47 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:59:49 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_sprite_printed(t_thread *data, int sprite_num, int i, int j)
{
	double	ratioSx;
	int		color;
	int		imgx;
	int		imgy;

	ratioSx = 1 - get_sprite_text(data->state,
			data->inter_sprite[sprite_num].coord, sprite_num);
	imgx = (data->state->text[4].width - 1) * ratioSx;
	imgy = (data->state->text[4].height - 1)
		* data->inter_sprite[sprite_num].coord.z;
	if (ratioSx >= 0 && ratioSx < 1)
	{
		color = *(unsigned int *)get_pixel(&data->state->text[4], imgx, imgy);
		if (color > 0xFF)
		{
			my_mlx_pixel_put(data->state, i, j, color);
			data->pxl_color = color;
			return (1);
		}
	}
	return (0);
}

int	ft_print_sprite(t_thread *data, int i, int j, int result)
{
	int		sprite_num;
	int		printed;

	sprite_num = -1;
	printed = 0;
	while (sprite_num != -2 && sprite_num < data->state->nb_sprites
		&& printed == 0)
	{
		sprite_num = ft_find_sprite(data->temp, data, sprite_num + 1);
		if (sprite_num != -2 && (result == 5
				|| data->inter_sprite[sprite_num].t < data->wall_text.t))
			printed = ft_is_sprite_printed(data, sprite_num, i, j);
	}
	return (printed);
}

void	print_south_or_north(t_thread *data, int result, int i, int j)
{
	double	decimal;
	int		imgx;
	int		imgy;

	decimal = data->inter1_wall.x
		- (double)(long int)data->inter1_wall.x;
	if (result == 3)
		decimal = 1 - decimal;
	imgx = (data->state->text[result].width - 1) * decimal;
	imgy = (data->state->text[result].height - 1) * data->inter1_wall.z;
	data->pxl_color = *(unsigned int *)get_pixel(&data->state->text[result],
			imgx, imgy);
	my_mlx_pixel_put(data->state, i, j, data->pxl_color);
}

void	ft_print_the_right_pixel(t_thread *data, int i, int j)
{
	int		result;
	double	decimal;
	int		imgx;
	int		imgy;

	data->wall_text = ft_find_texture(data, i, j);
	result = data->wall_text.result;
	if (ft_print_sprite(data, i, j, result) == 0)
	{
		if (result == 1 || result == 2)
		{
			decimal = data->inter2_wall.y
				- (double)(long int)data->inter2_wall.y;
			if (result == 2)
				decimal = 1 - decimal;
			imgx = (data->state->text[result].width - 1) * decimal;
			imgy = (data->state->text[result].height - 1) * data->inter2_wall.z;
			data->pxl_color = *(unsigned int *) \
			get_pixel(&data->state->text[result], imgx, imgy);
			my_mlx_pixel_put(data->state, i, j, data->pxl_color);
		}
		else if (result == 0 || result == 3)
			print_south_or_north(data, result, i, j);
	}
}
