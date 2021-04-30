/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:02:14 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 13:02:16 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	malloc_thread_data_stuff(t_state *state)
{
	state->thread_data[0].inter_sprite = malloc(state->nb_sprites
			* sizeof(t_inter));
	if (state->thread_data[0].inter_sprite == NULL)
		return (0);
	state->thread_data[1].inter_sprite = malloc(state->nb_sprites
			* sizeof(t_inter));
	if (state->thread_data[1].inter_sprite == NULL)
		return (0);
	state->thread_data[2].inter_sprite = malloc(state->nb_sprites
			* sizeof(t_inter));
	if (state->thread_data[2].inter_sprite == NULL)
		return (0);
	state->thread_data[3].inter_sprite = malloc(state->nb_sprites
			* sizeof(t_inter));
	if (state->thread_data[3].inter_sprite == NULL)
		return (0);
	return (1);
}

void	thread_create(t_state *state, int thread_id)
{
	state->thread_data[thread_id].thread_id = thread_id;
	state->thread_data[thread_id].state = state;
	state->thread_data[thread_id].inter1_wall.x = -1;
	state->thread_data[thread_id].inter1_wall.y = -1;
	state->thread_data[thread_id].inter1_wall.z = -1;
	state->thread_data[thread_id].inter2_wall.x = -1;
	state->thread_data[thread_id].inter2_wall.y = -1;
	state->thread_data[thread_id].inter2_wall.z = -1;
	if (pthread_create(&(state->thread_data[thread_id]).thread, NULL,
			(void *(*)(void *))thread_main,
		state->thread_data + thread_id) != 0)
	{
		printf("Error, problem with 'thread_create' !\n");
		ft_free_n_exit(state);
	}
}

void	*thread_main(t_thread *thread_data)
{
	ft_intersections(thread_data, thread_data->state->scale);
	return ((void *)0);
}
