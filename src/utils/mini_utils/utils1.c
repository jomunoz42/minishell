
#include "minishell.h"

int length_of_equal(char *vars)
{
    int i;

    i = 0;
    if (!vars)
        return(0);
    while(vars[i] && vars[i] != '=')
        i++;
    return (i);
}

int is_there_equal(char *vars)
{
    int i;

    i = 0;
    if (!vars)
        return(0);
    while(vars[i])
    {
        if (vars[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int is_there_value(char *vars)
{
    int i;

    i = 0;
    if (!vars)
        return(0);
    while(vars[i])
    {
        if (vars[i] == '=')
        {
            if (vars[i + 1] != '\0')
                return (1);
            else
                return (0);
        }
        i++;
    }
    return (0);
}

char	**sort_vars(char **vars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (vars[i] && vars[i + 1])
	{
		if (ft_strcmp(vars[i], vars[i + 1]) > 0)
		{
			tmp = vars[i];
			vars[i] = vars[i + 1];
			vars[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (vars);
}

int	if_key_exists(char *arg, t_map *env)
{
	t_node	*node;

	node = env->head;
	while (node)
	{
		if (!strncmp(node->key, arg, ft_strlen(arg) + 1))
			return (1);
		node = node->next;
	}
	env->put(env, "?", ft_strdup("0"));
	return (0);
}
