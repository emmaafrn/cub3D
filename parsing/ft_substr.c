#include "../cub3d.h"

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
		str = malloc(sizeof(char));
	else if (len > (ft_strlen(s) - start))
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != start && s[i])
		i++;
	while (s[i] && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
