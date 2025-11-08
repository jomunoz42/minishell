#include "minishell.h"

int	is_valid_pipe(char *str, int end)
{
	int	i;
    int count;

	i = 0;
    count = 0;
	while (i <= end)
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '|')
            count++;
        if (str[i] == '|' && count == 0)
            return (0);
        i++;
	}
    return (1);
}

int	check_sintax(char *str, t_map *env)
{
	int i;
	char flag;

	i = -1;
	// while (str[++i])
	// {
	// 	flag = identify_quote(str[i], flag);
	// 	if (flag)
	// 		continue ;
	// 	if (str[i] == '|' && !is_valid_pipe(str, i))
    //     {
    //         write(2, "bash: syntax error near unexpected token\n", 42);
    //         env->put(env, "?", ft_strdup("2"));
    //         return (0);
    //     }
	// }
	return (1);
}