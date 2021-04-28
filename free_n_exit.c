/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:58:43 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:58:46 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_free_rays(t_vector **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	ft_free_n_exit(t_state *state)
{
	if (state->dir_ray)
		ft_free_rays(state->dir_ray, (state->parse.Ry));
	if (state->y_plane)
		free(state->y_plane);
	if (state->x_plane)
		free(state->x_plane);
	if (state->sprite_tab)
		free(state->sprite_tab);
	exit(0);
	return (0);
}
