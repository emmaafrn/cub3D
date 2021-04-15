#include "cub3d.h"

double	get_vector_norm(t_vector U)
{
	double	vector_norm;

	vector_norm = sqrt(pow(U.x,2) + pow(U.y,2) + pow(U.z, 2));
	return (vector_norm);
}

double	get_sprite_text(t_state *state, t_coord I, int k)
{
	t_coord		P;
	t_vector	U;
	t_vector	V;
	t_vector	V2;
	double		r;

	P.x = state->sprite_tab[k].coord.x + 0.5;
	P.y = state->sprite_tab[k].coord.y + 0.5;
	P.z = I.z;
	U.x = I.x - P.x;
	U.y = I.y - P.y;
	U.z = I.z - P.z;
	V.x = P.x - state->player_pos.x;
	V.y = P.y - state->player_pos.y;
	V.z = 0;
	// if (get_vector_norm(U) > 0.5)
	// 	return (-1);
	V2.x = V.y / get_vector_norm(V);
	V2.y = -V.x / get_vector_norm(V);
	V2.z = 0;
	r = (U.x * V2.x) + (U.y * V2.y) + (U.z * V2.z) + 0.5;
	return (r);
}
