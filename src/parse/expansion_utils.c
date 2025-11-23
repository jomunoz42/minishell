/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:08 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/23 16:15:03 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (!ft_isalnum_modified(str[i]) && str[i] != '?' && str[i] != '$')
				continue ;
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

char	*expand_str(char *dest, char *src, int index, int n)
{
	int		d_len;
	int		s_len;
	int		var_size;
	int		tail_len;
	char	*new_str;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	var_size = check_size(dest + index + 1) + 1;
	tail_len = ft_strlen(dest + index + var_size);
	new_str = ft_calloc(s_len + d_len - var_size + 2, 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, dest, index);
	ft_memcpy(new_str + index + n, src, s_len);
	ft_memcpy(new_str + index + s_len + n, dest + index + var_size, tail_len);
	if (n)
		new_str[index] = '\2';
	free(dest);
	return (new_str);
}

char	*expanded_arg(char *str, t_map *env, int n)
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
				continue ;
			var = verify_var(str, env);
			if (!var)
				return (NULL);
			str = expand_str(str, var, i, n);
			if (!str)
				return (free(var), NULL);
			i = i + ft_strlen(var) - 1;
			free(var);
		}
	}
	return (str);
}
