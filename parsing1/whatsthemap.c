/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatsthemap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:25:41 by efarin            #+#    #+#             */
/*   Updated: 2021/02/15 14:25:44 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int		checkalltab(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j] && (tab[i][j] == ' ' || tab[i][j] == 'N'
		|| tab[i][j] == 'S' || tab[i][j] == 'E' || tab[i][j] == 'W'
		|| tab[i][j] == '1' || tab[i][j] == '2' || tab[i][j] == '0'))
		{
			if (tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'E'
			|| tab[i][j] == 'W')
			{
				if (mstruct->position != '0')
					return (0);
				mstruct->position = tab[i][j];
				mstruct->xplayer = j;
				mstruct->yplayer = i;
			}
			j++;
		}
		if (tab[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int		checkthenorth(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while ((tab[i][j] == '1' || tab[i][j] == ' ') && tab[i][j])
		j++;
	if (tab[i][j] == '\0')
		return (1);
	return (0);
}

int		checkspaces(char **tab, t_struct *mstruct, int i, int j)
{
	if (tab[i][j + 1] != ' ' && tab[i - 1][j] != ' ' && tab[i][j - 1] != ' ')
		return (1);
	return (0);
}

int		checkplayerposition(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = mstruct->yplayer;
	j = mstruct->xplayer;
	if (j == mstruct->lenmax || j == 0)
		return (0);
	if (i == 0 || )
	return (checkspaces(tab, mstruct, i, j));
}

int		thereiszeroortwo(int i, int j, char **tab, t_struct *mstruct)
{
	if (tab[i][j] == '0')
	{
		if (j == 0 || j == (mstruct->lenmax - 1) || tab[i + 1] == NULL)
			return (0);
		if (checkspaces(tab, mstruct, i, j) == 0)
			return (0);
	}
	else
	{
		if (j == 0 || j == (mstruct->lenmax - 1)|| tab[i + 1] == NULL)
			return (0);
		if (checkspaces(tab, mstruct, i, j) == 0)
			return (0);
	}
	return (1);
}

int		checkthemap(char **tab, t_struct *mstruct)
{
	int	i;
	int	j;

	i = 0;
	if (checkalltab(tab, mstruct) == 0 || checkthenorth(tab, mstruct) == 0
	|| mstruct->position == '0' || checkplayerposition(tab, mstruct) == 0)
		return (0);
	while (tab[i] != NULL)
	{
		j = 0;
		while (tab[i][j])
		{
			if ((tab[i][j] == '0' || tab[i][j] == '2')
			&& thereiszeroortwo(i, j, tab, mstruct) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
