/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacenplayerpos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:57:09 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:57:11 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkspaces(char **tab, int i, int j)
{
	if (tab[i][j + 1] != ' ' && tab[i - 1][j] != ' ' && tab[i][j - 1] != ' ')
		return (1);
	return (0);
}

int	checkplayerposition(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (tab[k])
		k++;
	i = mstruct->yplayer;
	j = mstruct->xplayer;
	if (i == k - 1 || i == 0 || j == 0 || j == mstruct->lenmax - 1)
		return (0);
	return (checkspaces(tab, i, j));
}
