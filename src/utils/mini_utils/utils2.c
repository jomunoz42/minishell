#include "minishell.h"

char *ft_realloc_str(char *str, int len)
{
    char *new;

    new = malloc(len);
    if (!new)
        return(free(str), NULL);
    if (str)
        ft_strlcpy(new, str, len);
    else
        new[0] = '\0';
    free(str);
    return (new);
}

int	arr_count(char **arr)
{
	int	i;

	i = 0;
    if (!arr)
            return (0);
	while (arr[i])
		i++;
	return (i);
}
