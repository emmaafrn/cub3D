/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrmalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:54:57 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:55:03 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	**wrgetter(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*wrmalloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	buffer = malloc(size);
	if (!(buffer))
	{
		wrdestroy();
		return (0);
	}
	new_elem = malloc(sizeof(t_list));
	if (!(new_elem))
	{
		free(buffer);
		wrdestroy();
		return (0);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(wrgetter(), new_elem);
	return (buffer);
}

int	wrfree(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	wrdestroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
