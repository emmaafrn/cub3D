#include "cub3d.h"

double	ft_fmax(double a, double b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

double	ft_fmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

t_coord	rectif_pos(t_state *state, t_plane plane, t_coord inter)
{
	if (ft_fmax(inter.y, plane.d) -
		ft_fmin(inter.y, plane.d) <= 0.0001)
	{
		if (state->player_pos.y < inter.y)
			inter.y = plane.d;
		else
			inter.y = plane.d - 1;
	}
	else if (ft_fmax(inter.x, plane.d) -
		ft_fmin(inter.x, plane.d) <= 0.0001)
	{
		if (state->player_pos.x < inter.x)
			inter.x = plane.d;
		else
			inter.x = plane.d - 1;
	}
	return (inter);
}
