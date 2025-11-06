#include "minishell.h"

int		verify_var_sintax(char *str);

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

char	*get_expansion(char *var, t_map *env)
{
	char	*tmp;

	if (var[0] == '0')
		tmp = ft_strdup("bash");
	else
		tmp = ft_strdup(env->get(env, var));
	if (!tmp)
		return (NULL);
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

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	var_size = check_size(dest + index + 1) + 1;
	tail_len = ft_strlen(dest + index + var_size);
	if (*src)
	{
		dest = ft_realloc_str(dest, s_len + d_len - var_size + 2);
		if (!dest)
			return (NULL);
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
				return (free(var), NULL);
			i = i + ft_strlen(var) - 1;
			free(var);
		}
	}
	return (str);
}
