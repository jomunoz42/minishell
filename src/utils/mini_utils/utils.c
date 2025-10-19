#include "minishell.h"

void 	error_exit(char *s, int code)
{
    errno = code;
    perror(s);
    exit(0);
}

void	free_double(char **arg)
{
	int i;

	i = 0;
	if (!arg || !*arg)
		return ;
    while (arg[i])
        free(arg[i++]);
    free(arg);
    return ;
}

char *ft_realloc(char *str, int len)
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *result;
	
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
