

#include "minishell.h"

int	ft_lstsize(t_cmd *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
