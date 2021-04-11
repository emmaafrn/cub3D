#include "../cub3d.h"

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
