#include "cub3d.h"

char	*ft_free_rays(t_vector **tab, size_t i)
{
	while (i-- > 0)
		wrfree(tab[i]);
	wrfree(tab);
	return (NULL);
}

int	ft_free_n_exit(t_state *state)
{
	ft_free_rays(state->dir_ray, (state->parse.Rx * state->parse.Ry));
	free(state->y_plane);
	free(state->x_plane);
	if (state->sprite_tab)
		free(state->sprite_tab);
	exit(0);
	return (0);
}
