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
		return ;
}

void	*thread_main(t_thread *thread_data)
{
	ft_intersections(thread_data, 2);
	return ((void *)0);
}
