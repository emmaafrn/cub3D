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

void	thread_create(t_state *state)
{
	state->thread_data.state = state;
	if (pthread_create(&state->thread_data.thread, NULL, (void *(*)(void *))thread_main, &state->thread_data) != 0)
		return ;
	if (pthread_detach(state->thread_data.thread) != 0)
		return ;
	if (pthread_mutex_init(&state->thread_data.mutex, NULL) != 0)
		return ;
	state->thread_data.inter1_wall.x = -1;
	state->thread_data.inter1_wall.y = -1;
	state->thread_data.inter1_wall.z = -1;
	state->thread_data.inter2_wall.x = -1;
	state->thread_data.inter2_wall.y = -1;
	state->thread_data.inter2_wall.z = -1;
	if (pthread_cond_init(&state->thread_data.done_cond, NULL) != 0)
		return ;
	pthread_mutex_lock(&state->thread_data.mutex);
}

void	init_multi_thread(t_state *state)
{
	if (pthread_cond_init(&state->render_cond, NULL) != 0)
		return ;
}

void	*thread_main(t_thread *thread_data)
{
	thread_data->inter_sprite = malloc(thread_data->state->nb_sprites * sizeof(t_inter));
	// if (!state->thread_data.inter_sprite)
	// 	return ;
	while (1)
	{
		pthread_cond_wait(&thread_data->state->render_cond,&thread_data->mutex);
		ft_intersections(thread_data, 2);
		pthread_mutex_lock(&thread_data->mutex);
		pthread_cond_signal(&thread_data->done_cond);
	}
	return ((void *)0);
}
