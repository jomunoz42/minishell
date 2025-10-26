

#include "minishell.h"

static void	print_export(char **vars)
{
	int	i;

	i = 0;
	while (vars && vars[i])
	{
		if (ft_strncmp(vars[i], "_=\"./minishell\"", 16) == 0)
		{
			i++;
			continue ;
		}
		printf("declare -x %s\n", vars[i]);
		i++;
	}
	free(vars);
}

static char	**sort_vars(char **vars)
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

static void	add_export(char *arg, t_map *env)
{
	char	**vars;
	int		j;

	vars = ft_calloc(sizeof(char *), 3);
	if (!vars)
		ft_exit(1);
	if (is_there_equal(arg))
	{
		j = length_of_equal(arg);
		vars[0] = ft_substr(arg, 0, j++);
		if (is_there_value(arg))
			vars[1] = ft_substr(arg, j, (ft_strlen(arg) - j));
		else
			vars[1] = ft_strdup("");
		env->put(env, vars[0], vars[1]);
	}
	else
		env->put(env, ft_strdup(arg), NULL);
}

char	*create_var(t_node *node)
{
	char	*str;
	char	*new_value;
	char	*result;

	if (node->value)
	{
		str = ft_strjoin(node->key, "=\"");
		new_value = ft_strjoin(node->value, "\"");
		result = ft_strjoin_free(str, new_value);
		free(new_value);
	}
	else
		result = ft_strdup(node->key);
	return (result);
}

void	ft_export(t_cmd *cmd, t_map *env, t_exec *x) //  REMEMBER TO TEST THE CHANGE (NO SOUBLE SORT)
{
	t_node	*node;
	char	**copy;
	int		i;

	i = 1;
	if (cmd->args[i])
	{
		while (cmd->args[i])
			add_export(cmd->args[i++], env);
	}
	else
	{
		copy = ft_calloc(sizeof(char *), env->size + 1);
		if (!copy)
			ft_exit(1);
		node = env->head;
		i = 0;
		while (node)
		{
			copy[i++] = create_var(node);
			node = node->next;
		}
		copy[i] = NULL;
		print_export(sort_vars(copy));
	}
}
