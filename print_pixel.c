#include "cub3d.h"

int	ft_is_sprite_printed(t_state *state, int sprite_num, int i, int j)
{
	double	ratioSx;
	int		color;
	int		imgx;
	int		imgy;

	ratioSx = 1 - get_sprite_text(state, state->sprite_tab[sprite_num].inter.coord, \
		sprite_num);
	imgx = (state->text[4].width - 1) * ratioSx;
	imgy = (state->text[4].height - 1)
		* state->sprite_tab[sprite_num].inter.coord.z;
	if (ratioSx >= 0 && ratioSx < 1)
	{
		color = *(unsigned int *)get_pixel(&state->text[4], imgx, imgy);
		if (color > 0xFF)
		{
			my_mlx_pixel_put(state, i, j, color);
			state->pxl_color = color;
			return (1);
		}
	}
	return (0);
}

int	ft_print_sprite(t_state *state, int i, int j, int result)
{
	int		sprite_num;
	int		printed;
	int		color;

	sprite_num = -1;
	printed = 0;
	while (sprite_num != -2 && sprite_num < state->nb_sprites && printed == 0)
	{
		sprite_num = \
		ft_find_sprite(state->dir_ray[j][i], state, sprite_num + 1);
		if (sprite_num != -2 && (result == 5 \
		|| state->sprite_tab[sprite_num].inter.t < state->wall_text.t))
			printed = ft_is_sprite_printed(state, sprite_num, i, j);
	}
	return (printed);
}

void	ft_print_the_right_pixel(t_state *state, int i, int j)
{
	int		result;
	double	decimal;
	int		imgx;
	int		imgy;

	state->wall_text = ft_find_texture(state, i, j);
	result = state->wall_text.result;
	if (ft_print_sprite(state, i, j, result) == 0)
	{
		if (result == 1 || result == 2)
		{
			decimal = state->inter2_wall.y - (double)(long int)state->inter2_wall.y;
			if (result == 2)
				decimal = 1 - decimal;
			imgx = (state->text[result].width - 1) * decimal;
			imgy = (state->text[result].height - 1) * state->inter2_wall.z;
			state->pxl_color = *(unsigned int *)get_pixel(&state->text[result], imgx, imgy)
			my_mlx_pixel_put(state, i, j, state->plx_color);
		}
		else if (result == 0 || result == 3)
		{
			decimal = state->inter1_wall.x - (double)(long int)state->inter1_wall.x;
			if (result == 3)
				decimal = 1 - decimal;
			imgx = (state->text[result].width - 1) * decimal;
			imgy = (state->text[result].height - 1) * state->inter1_wall.z;
			state->pxl_color = *(unsigned int *)get_pixel(&state->text[result], imgx, imgy)
			my_mlx_pixel_put(state, i, j, state->plx_color);
		}
	}
}
