/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 08:53:36 by efarin            #+#    #+#             */
/*   Updated: 2021/04/28 08:53:46 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		str = wrmalloc(sizeof(char));
	else if (len > (ft_strlen(s) - start))
		str = wrmalloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = wrmalloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != start && s[i])
		i++;
	while (s[i] && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
