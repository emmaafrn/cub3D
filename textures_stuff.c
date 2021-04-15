#include "cub3d.h"

char	*get_pixel(t_textures *text, int x, int y)
{
	char	*dst;

	dst = text->addr + ((text->height - y - 1) * text->line_length \
	+ x * (text->bits_per_pixel / 8));
	return (dst);
}

t_wall_text	ft_texture(double t1, double t2, int text1, int text2)
{
	t_wall_text	wall_text;

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

t_eastnwest	check_east_n_west(t_state *state, int j, int i, t_eastnwest res)
{
	if (state->dir_ray[j][i].x >= 0)
	{
		res.t2 = check_east(state, i, j);
		res.text2 = 1;
	}
	else if (state->dir_ray[j][i].x <= 0)
	{
		res.t2 = check_west(state, i, j);
		res.text2 = 2;
	}
	return (res);
}

t_wall_text	ft_find_texture(t_state *state, int i, int j)
{
	t_eastnwest	res;
	double		t1;
	int			text1;

	res.t2 = -1;
	if (state->dir_ray[j][i].y <= 0)
	{
		t1 = check_north(state, i, j);
		text1 = 0;
		res = check_east_n_west(state, j, i, res);
	}
	else
	{
		t1 = check_south(state, i, j);
		text1 = 3;
		res = check_east_n_west(state, j, i, res);
	}
	return (ft_texture(t1, res.t2, text1, res.text2));
}
