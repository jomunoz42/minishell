#include "minishell.h"

char	*verify_var(char *str, t_map *env)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			j = 0;
			while (str[i + j] && str[i + j + 1] != ' ' && str[i + j + 1] != '"'
				&& str[i + j + 1] != '\'')
				j++;
			var = ft_substr(str, i + 1, j);
			if (!var)
				return (NULL);
			str = ft_strdup(env->get(env, var));
			free(var);
			if (!str)
				return (NULL);
			break ;
		}
		i++;
	}
	return (str);
}

int	check_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
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
	var_size = check_size(dest + index);
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
	free(src);
	return (dest);
}

char	*expanded_arg(char *str, t_map *env)
{
	int		i;
	char	*var;
	bool	s_flag;
	bool	d_flag;

	i = -1;
	s_flag = false;
	d_flag = false;
	while (str[++i])
	{
		if (!s_flag && str[i] == '"')
			d_flag = !d_flag;
		if (!d_flag && str[i] == '\'')
			s_flag = !s_flag;
		if (!s_flag && str[i] == '$' || d_flag && str[i] == '$')
		{
			var = verify_var(str, env);
			if (!var)
				return (NULL);
			str = expand_str(str, var, i);
			if (!str)
				return (NULL);
		}
	}
	return (str);
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
	return (0);
}
