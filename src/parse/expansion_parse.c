#include "minishell.h"

int	check_size(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	if (str[i] == '?' || str[i] == '$')
		return (1);
	while (str[i] && ft_isalnum_modified(str[i]))
		i++;
	return (i);
}

int	verify_var_sintax(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = check_size(str);
	if (!ft_isalnum_modified(str[i]) && str[i] != '?' && str[i] != '$')
		return (0);
	while (i < j && str[i])
	{
		if (!ft_isalnum_modified(str[i++]))
			return (0);
	}
	return (1);
}

char	*verify_var(char *str, t_map *env)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (str[i] == '0')
			{
				str = ft_strdup("bash");
				break ;
			}
			j = check_size(str + i);
			var = ft_substr(str, i, j);
			if (!var)
				return (NULL);
			str = ft_strdup(env->get(env, var));
			free(var);
			break ;
		}
	}
	if (!str)
		return (NULL);
	return (str);
}

char	*expand_str(char *dest, char *src, int index)
{
	int		d_len;
	int		s_len;
	int		var_size;
	int		tail_len;
	char	*tmp;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	var_size = check_size(dest + index + 1) + 1;
	tail_len = ft_strlen(dest + index + var_size);
	if (*src)
	{
		tmp = ft_realloc_str(dest, s_len + d_len - var_size + 1);
		if (!tmp)
			return (NULL);
		dest = tmp;
	}
	ft_memmove(dest + index + s_len, dest + index + var_size, tail_len + 1);
	ft_memcpy(dest + index, src, s_len);
	return (dest);
}

char	*expanded_arg(char *str, t_map *env)
{
	int		i;
	char	*var;
	char	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		flag = identify_quote(str[i], flag);
		if (flag != '\'' && str[i] == '$' && str[i + 1])
		{
			if (!verify_var_sintax(str + i))
				break ;
			var = verify_var(str, env);
			if (!var)
				return (NULL);
			str = expand_str(str, var, i);
			if (!str)
				return (NULL);
			i = i + ft_strlen(var) - 1;
			free(var);
		}
	}
	return (str);
}

int organize_args(char **args)
{
	int i;
	int j;

	i = 0;
	while (args[i])
	{
		if (!*args[i] && args[i + 1])
		{
			j = 0;
			while (args[i + j + 1])
			{
				args[i + j] = args[ i + j + 1];
				j++;
			}
			args[i + j] = NULL;
		}
		i++;
	}
	if (!*args[0])
		return (0);
	return (1);
}

int organize_list(t_cmd *head)
{
	t_cmd *node;

	node = head;
	while (node)
	{
		if (!organize_args(node->args))
			return (0);
		node = node ->next;
	}
	return (1);
}

int	change_expansion(t_cmd *head, t_map *env)
{
	int		i;
	char	*str;
	t_cmd	*node;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			node->args[i] = expanded_arg(node->args[i], env);
			if (!node->args[i])
				return (0);
			i++;
		}
		node = node->next;
	}
	if (!organize_list(head))
		return (0);
	return (1);
}
