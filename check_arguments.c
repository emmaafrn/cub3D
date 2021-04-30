/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:20:48 by efarin            #+#    #+#             */
/*   Updated: 2021/04/30 09:20:50 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_arguments(t_state *state, int arc, char **arv)
{
	if (arc == 1)
	{
		printf("Error, no arguments !\n");
		exit(0);
	}
	if (arc > 3)
	{
		printf("Error, invalid arguments !\n");
		exit(0);
	}
	if (arc == 3)
	{
		if (arv[2][0] == '-'
		&& arv[2][1] == '-' && arv[2][2] == 's'
		&& arv[2][3] == 'a' && arv[2][4] == 'v'
		&& arv[2][5] == 'e' && arv[2][6] == '\0')
			state->save = 1;
		else
		{
			printf("Error, invalid arguments !\n");
			exit(0);
		}
	}
	else
		state->save = 0;
}
