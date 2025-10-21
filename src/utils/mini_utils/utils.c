
#include "minishell.h"

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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *result;
	
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
