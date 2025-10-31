#include "minishell.h"

void error_exit(char *s, int code)
{
    errno = code;
    perror(s);
    exit(0);
}

char *ft_realloc_str(char *str, int len)
{
    int i;
    char *new;

    new = malloc(len);
    if (!new)
        return(free(str), NULL);
    if (str)
    {
        ft_strlcpy(new, str, len);
        free(str);
    }
    else
        new[0] = '\0';
    return (new);
}

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
