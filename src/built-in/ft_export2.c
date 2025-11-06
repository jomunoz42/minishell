

#include "minishell.h"

int	if_key_exists(char *arg, t_map *env)
{
	t_node	*node;

	node = env->head;
	while (node)
	{
		if (!strncmp(node->key, arg, ft_strlen(arg) + 1))
		{
			env->put(env, "?", ft_strdup("1"));
			return (1);
		}
		node = node->next;
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

int	handle_invalid_export(char *arg, t_map *env)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if (ft_isdigit(arg[0]) || !ft_isalnum_modified(arg[i]))
		{
			write(2, "bash: export: `", 15);
			write(2, arg, ft_strlen(arg));
			write(2, "': not a valid identifier\n", 27);
			env->put(env, "?", ft_strdup("1"));
			return (1);
		}
	}
	return (0);
}
