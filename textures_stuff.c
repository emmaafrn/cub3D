/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 09:00:55 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 09:00:57 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_pixel(t_textures *text, int x, int y)
{
	char	*dst;

	dst = text->addr + ((text->height - y - 1) * text->line_length \
	+ x * (text->bits_per_pixel / 8));
	return (dst);
}

inline t_wall_text	ft_texture(double t1, double t2, int text1, int text2)
{
	t_wall_text	wall_text;

	wall_text.result = 0;
	wall_text.t = 0;
	if (t1 == -1 && t2 == -1)
	{
		wall_text.t = -1;
		wall_text.result = 5;
	}
	else if (t2 == -1 || (t1 < t2 && t1 != -1))
	{
		wall_text.t = t1;
		wall_text.result = text1;
	}
	else if (t1 == -1 || (t2 < t1 && t2 != -1))
	{
		wall_text.t = t2;
		wall_text.result = text2;
	}
	return (wall_text);
}

inline t_eastnwest	check_east_n_west(t_thread *data, int j, int i, t_eastnwest res)
{
	if (data->temp.x >= 0)
	{
		res.t2 = check_east(data, i, j);
		res.text2 = 1;
	}
	else if (data->temp.x <= 0)
	{
		res.t2 = check_west(data, i, j);
		res.text2 = 2;
	}
	return (res);
}

t_wall_text	ft_find_texture(t_thread *data, int i, int j)
{
	t_eastnwest	res;
	double		t1;
	int			text1;

	res.t2 = -1;
	if (data->temp.y <= 0)
	{
		t1 = check_north(data, i, j);
		text1 = 0;
		res = check_east_n_west(data, j, i, res);
	}
	else
	{
		t1 = check_south(data, i, j);
		text1 = 3;
		res = check_east_n_west(data, j, i, res);
	}
	return (ft_texture(t1, res.t2, text1, res.text2));
}
