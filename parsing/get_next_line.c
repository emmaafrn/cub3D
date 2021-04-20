/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:59:09 by efarin            #+#    #+#             */
/*   Updated: 2021/04/14 16:50:39 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../get_next_line.h"

int	ret_free(char **line)
{
	wrfree(*line);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	t_gnl	gnl;

	gnl.l = 1;
	*line = wrmalloc(gnl.l);
	if (!(*line))
		return (-1);
	(*line)[0] = 0;
	gnl.r = read(fd, &gnl.c, 1);
	while ((gnl.r) && gnl.l++ && gnl.c != '\n')
	{
		gnl.tmp = wrmalloc(gnl.l);
		if (!(gnl.tmp))
			ret_free(line);
		gnl.i = -1;
		while (++gnl.i < gnl.l - 2)
			gnl.tmp[gnl.i] = (*line)[gnl.i];
		gnl.tmp[gnl.i] = gnl.c;
		gnl.tmp[gnl.i + 1] = 0;
		wrfree(*line);
		*line = gnl.tmp;
		gnl.r = read(fd, &gnl.c, 1);
	}
	return (gnl.r);
}
