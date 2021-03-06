/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getlenmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:55:29 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:55:34 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	getlenmax(t_list **alst)
{
	int		len;
	t_list	*lst;
	int		lenmax;

	lst = *alst;
	lenmax = 0;
	while (lst->next != NULL)
	{
		len = ft_strlen(lst->content);
		if (len > lenmax)
			lenmax = len;
		lst = lst->next;
	}
	return (lenmax);
}
