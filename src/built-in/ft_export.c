

#include "minishell.h"

char		**sort_vars(char **vars);
int			if_key_exists(char *arg, t_map *env);
int			handle_invalid_export(char *arg, t_map *env);

static int	print_export(char **vars, t_map *env, t_exec *exec)
{
	int	i;

	i = -1;
	while (vars && vars[++i])
	{
		if (!ft_strncmp(vars[i], "_=\"./minishell\"", 16)
			|| !ft_strncmp(vars[i], "?", 1) || !ft_strncmp(vars[i], "$", 1))
			continue ;
		write(exec->out, "declare -x ", 11);
		write(exec->out, vars[i], ft_strlen(vars[i]));
		write(exec->out, "\n", 1);
	}
	free(vars);
	return (0);
}

static int	add_export(char *arg, t_map *env)
{
	char	**vars;
	int		j;

	if (handle_invalid_export(arg, env))
		return (1);
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
	{
		if (if_key_exists(arg, env))
			return (1);
		env->put(env, ft_strdup(arg), NULL);
	}
	return (0);
}

static char	*create_var(t_node *node)
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

static int  export_var(t_cmd *cmd, t_map *env, int i)
{
	int invalid_export;

	invalid_export = 0;
	while (cmd->args[i])
	{
		if (add_export(cmd->args[i], env))
			invalid_export = 1;
		i++;
	}
	return (invalid_export);
}

int	ft_export(t_cmd *cmd, t_map *env, t_exec *exec)
{
	t_node	*node;
	char	**copy;
	int		i;

	i = 1;
	if (cmd->args[i])
		return (export_var(cmd, env, i));
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
		return (print_export(sort_vars(copy), env, exec));
	}
}

