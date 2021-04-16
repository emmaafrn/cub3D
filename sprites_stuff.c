#include "cub3d.h"

void	ft_mem_sprite_tab(t_state *state)
{
	int	x;
	int	y;
	int	nb;

	y = 0;
	nb = 0;
	while (y < mapHeight)
	{
		x = 0;
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 2)
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
	while (y < mapHeight)
	{
		x = 0;
		while (x < mapWidth)
		{
			if (worldMap[y][x] == 2)
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

void	ft_sort_sprites(t_state *state)
{
	double	dist_min;
	t_vector	v;
	t_sprite	temp;
	double	dist;
	int	i;
	int	j;

	i = 0;
	dist = INT_MAX;
	while (i < state->nb_sprites)
	{
		v.x = (state->sprite_tab[i].coord.x + 0.5)- state->player_pos.x;
		v.y = (state->sprite_tab[i].coord.y + 0.5) - state->player_pos.y;
		v.z = 0;
		dist_min = get_vector_norm(v);
		j = state->nb_sprites - 1;
		while (dist >= dist_min && j > i)
		{
			v.x = (state->sprite_tab[j].coord.x + 0.5) - state->player_pos.x;
			v.y = (state->sprite_tab[j].coord.y + 0.5) - state->player_pos.y;
			v.z = 0;
			dist = get_vector_norm(v);
			if (dist < dist_min)
			{
				temp = state->sprite_tab[i];
				state->sprite_tab[i] = state->sprite_tab[j];
				state->sprite_tab[j] = temp;
				dist_min = dist;
			}
			j--;
		}
		i++;
	}
}

void	ft_planes_sprites(t_state *state)
{
	int			i;
	t_vector	v;

	ft_mem_sprite_tab(state);
	ft_coord_sprites(state);
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
			if ((int)inter.coord.x >= 0 && (int)inter.coord.x < mapWidth \
			&& ((int)inter.coord.y >= 0 && (int)inter.coord.y < mapHeight) \
			&& worldMap[(int)inter.coord.y][(int)inter.coord.x] == 2)
			{
				return (ft_keep_inter(state, inter, k, t));
			}
		}
		k++;
	}
	return (-2);
}
