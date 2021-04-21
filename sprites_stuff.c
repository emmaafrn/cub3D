#include "cub3d.h"

void	ft_mem_sprite_tab(t_state *state)
{
	int	x;
	int	y;
	int	nb;

	y = 0;
	nb = 0;
	while (y < state->parse.hmap)
	{
		x = 0;
		while (x < state->parse.lenmax)
		{
			if (state->parse.map[y][x] == '2')
				nb++;
			x++;
		}
		y++;
	}
	state->nb_sprites = nb;
	state->sprite_tab = malloc(nb * sizeof(t_sprite));
	if (state->sprite_tab == NULL)
		return ;
}

void	ft_coord_sprites(t_state *state)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < state->parse.hmap)
	{
		x = 0;
		while (x < state->parse.lenmax)
		{
			if (state->parse.map[y][x] == '2')
			{
				state->sprite_tab[i].coord.x = x;
				state->sprite_tab[i].coord.y = y;
				state->sprite_tab[i].coord.z = 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	ft_planes_sprites(t_state *state)
{
	int			i;
	t_vector	v;

	ft_sort_sprites(state);
	i = 0;
	while (i < state->nb_sprites)
	{
		v.x = state->sprite_tab[i].coord.x + 0.5 - (state->player_pos.x);
		v.y = state->sprite_tab[i].coord.y + 0.5 - (state->player_pos.y);
		v.z = state->sprite_tab[i].coord.z - state->player_pos.z;
		state->sprite_tab[i].plane.a = v.x;
		state->sprite_tab[i].plane.b = v.y;
		state->sprite_tab[i].plane.c = v.x;
		state->sprite_tab[i].plane.d = -(v.x * (state->sprite_tab[i].coord.x \
		+ 0.5)) - (v.y * (state->sprite_tab[i].coord.y + 0.5)) \
		- (v.z * state->sprite_tab[i].coord.z);
		i++;
	}
}

int	ft_keep_inter(t_state *state, t_inter inter, int k, double t)
{
	state->sprite_tab[k].inter.coord.x = inter.coord.x;
	state->sprite_tab[k].inter.coord.y = inter.coord.y;
	state->sprite_tab[k].inter.coord.z = inter.coord.z;
	state->sprite_tab[k].inter.t = t;
	return (k);
}

int	ft_find_sprite(t_vector dir, t_state *state, int sprite_num)
{
	int			k;
	double		t;
	t_inter		inter;

	k = sprite_num;
	while (k < state->nb_sprites)
	{
		t = ft_distance(state, state->sprite_tab[k].plane, dir);
		inter.coord.x = state->player_pos.x + (t * dir.x);
		inter.coord.y = state->player_pos.y + (t * dir.y);
		inter.coord.z = state->player_pos.z + (t * dir.z);
		inter.coord =\
		rectif_pos(state, state->sprite_tab[k].plane, inter.coord);
		if (t > 0 && inter.coord.z >= 0 && inter.coord.z <= 1)
		{
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < state->parse.lenmax \
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < state->parse.hmap) \
			&& state->parse.map[(int)inter.coord.y][(int)inter.coord.x] == '2')
				return (ft_keep_inter(state, inter, k, t));
		}
		k++;
	}
	return (-2);
}
