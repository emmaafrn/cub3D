#include "cub3d.h"

void	mlx_get_texture(t_state *state)
{
	state->text[0].img = mlx_png_file_to_image(state->mlx, "./png/mossy.png", \
	&state->text[0].width, &state->text[0].height);
	state->text[0].addr = mlx_get_data_addr(state->text[0].img, &state->text[0].bits_per_pixel, \
	&state->text[0].line_length, &state->text[0].endian);
	state->text[1].img = mlx_png_file_to_image(state->mlx, "./png/greystone.png", \
	&state->text[1].width, &state->text[1].height);
	state->text[1].addr = mlx_get_data_addr(state->text[1].img, &state->text[1].bits_per_pixel, \
	&state->text[1].line_length, &state->text[1].endian);
	state->text[2].img = mlx_png_file_to_image(state->mlx, "./png/redbrick.png", \
	&state->text[2].width, &state->text[2].height);
	state->text[2].addr = mlx_get_data_addr(state->text[2].img, &state->text[2].bits_per_pixel, \
	&state->text[2].line_length, &state->text[2].endian);
	state->text[3].img = mlx_png_file_to_image(state->mlx, "./png/purplestone.png", \
	&state->text[3].width, &state->text[3].height);
	state->text[3].addr = mlx_get_data_addr(state->text[3].img, &state->text[3].bits_per_pixel, \
	&state->text[3].line_length, &state->text[3].endian);
	state->text[4].img = mlx_xpm_file_to_image(state->mlx, "./xpm/sprite.xpm", \
	&state->text[4].width, &state->text[4].height);
	state->text[4].addr = mlx_get_data_addr(state->text[4].img, &state->text[4].bits_per_pixel, \
	&state->text[4].line_length, &state->text[4].endian);
}

char	*get_pixel(t_textures *text, int x, int y)
{
	char	*dst;

	dst = text->addr + ((text->height - y - 1) * text->line_length \
	+ x * (text->bits_per_pixel / 8));
	return (dst);
}

t_wall_text	ft_texture(double t1, double t2, int text1, int text2)
{
	t_wall_text		wall_text;

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

t_wall_text	ft_find_texture(t_state *state, int i, int j)
{
	double	t1;
	double	t2;
	int		text1;
	int		text2;

	t2 = -1;
	if (state->dir_ray[j][i].y <= 0 && !(text1 = 0))
	{
		t1 = check_north(state, i, j);
		if (state->dir_ray[j][i].x >= 0 && (text2 = 1))
			t2 = check_east(state, i, j);
		else if (state->dir_ray[j][i].x <= 0 && (text2 = 2))
			t2 = check_west(state, i, j);
	}
	else
	{
		t1 = check_south(state, i, j);
		text1 = 3;
		if (state->dir_ray[j][i].x >= 0 && (text2 = 1))
			t2 = check_east(state, i, j);
		else if (state->dir_ray[j][i].x <= 0 && (text2 = 2))
			t2 = check_west(state, i, j);
	}
	return (ft_texture(t1, t2, text1, text2));
}
