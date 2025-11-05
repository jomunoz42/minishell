#include "minishell.h"

int	quote_count(char *str);

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

char	*get_expansion(char *var, t_map *env)
{
	char	*tmp;

	// char	*str;
	// int		len;
	if (var[0] == '0')
		tmp = ft_strdup("bash");
	else
		tmp = ft_strdup(env->get(env, var));
	if (!tmp)
		return (NULL);
	// len = ft_strlen(tmp);
	// str = ft_calloc(len + 2, 1);
	// str[0] = '!';
	// ft_memcpy(str + 1, tmp, len);
	// str[len + 1] = '!';
	// free(tmp);
	return (tmp);
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
			j = check_size(str + i);
			var = ft_substr(str, i, j);
			if (!var)
				return (NULL);
			str = get_expansion(var, env);
			if (!str)
				return (NULL);
			free(var);
			break ;
		}
	}
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
		tmp = ft_realloc_str(dest, s_len + d_len - var_size + 2);
		if (!tmp)
			return (NULL);
		dest = tmp;
	}
	ft_memmove(dest + index + s_len + 1, dest + index + var_size, tail_len + 1);
	ft_memcpy(dest + index + 1, src, s_len);
	dest[index] = '&';
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

int	organize_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if (!*args[i] && args[i + 1])
		{
			j = 0;
			while (args[i + j + 1])
			{
				args[i + j] = args[i + j + 1];
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

char	*teste(char *splited, int gambiarra)
{
	int		len;
	char	*str;

	len = ft_strlen(splited);
	str = ft_calloc(len + gambiarra + 2, 1);
	if (!str)
		return (NULL);
	if (splited[0] == '&')
		splited++;
	str[0] = '!';
	ft_memcpy(str + 1, splited, len + 1);
	str[len + gambiarra] = '!';
	str[len + gambiarra + 1] = 0;
	return (str);
}

char	**new_args_expanded(char **splited, t_cmd *node, int start)
{
	int		j;
	int		i;
	char	**new_args;

	new_args = ft_calloc(arr_count(node->args) + arr_count(splited),
			sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (node->args[i])
	{
		if (i == start)
		{
			j = -1;
			while (++j < arr_count(splited))
				new_args[i + j] = teste(splited[j], 1);
		}
		else
			new_args[i] = node->args[i];
		i = i + arr_count(splited);
	}
	free_double(splited);
	return (new_args);
}

int	split_expansion_helper(t_cmd *node, int i)
{
	char	**tmp;

	tmp = ft_split(node->args[i], '\3');
	if (!tmp)
		return (0);
	if (arr_count(tmp) > 1)
	{
		node->args = new_args_expanded(tmp, node, i);
		if (!node->args)
			return (0);
	}
	else if (node->args[i][0] == '&')
	{
		node->args[i] = teste(node->args[i], 0);
		printf("NEW_ARGS: %s\n", node->args[i]);
		free_double(tmp);
	}
	return (1);
}

int	split_expansion(t_cmd *head)
{
	int		i;
	char	**tmp;
	t_cmd	*node;

	node = head;
	while (node)
	{
		i = -1;
		while (node->args[++i])
		{
			quote_handler(node->args[i]);
			if (!split_expansion_helper(node, i))
				return (0);
		}
		node = node->next;
	}
	return (1);
}

int	organize_list(t_cmd *head)
{
	t_cmd	*node;

	node = head;
	while (node)
	{
		if (!organize_args(node->args))
			return (0);
		node = node->next;
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
	if (!organize_list(head) || !split_expansion(head))
		return (0);
	return (1);
}
