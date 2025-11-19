/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:35 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/19 18:39:42 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_redir(char *str)
{
	int		i;
	char	last_char;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			last_char = str[i];
	}
	if (last_char == '>' || last_char == '<')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '<' && str[i] != '>')
			return (1);
		i++;
	}
	return (0);
}

int	double_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == ' ')
		{
			i++;
			while (str[i + 1] && str[i] == ' ')
				i++;
			if (str[i] == '>' || str[i] == '|')
				return (0);
		}
		else if (str[i] == '>' && str[i + 1] == ' ')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '<' || str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_redir(char *str, int end)
{
	int		i;
	char	c;
	int		count;

	i = 0;
	count = 0;
	if (!only_redir(str) || !double_redir(str))
			return (0);
	while (i <= end)
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (count == 0)
				c = str[i];
			if (c != str[i])
				return (0);
			count++;
		}
		else
			count = 0;
		if (count > 2)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_pipe(char *str, int end)
{
	int		i;
	int		count;
	char	last_char;

	i = 0;
	count = 0;
	while (i <= end)
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '|')
			count++;
		if (str[i] == '|' && count == 0)
			return (0);
		i++;
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			last_char = str[i];
	}
	if (last_char == '|')
		return (0);
	return (1);
}

int	check_sintax(char *str, t_map *env)
{
	int		i;
	char	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		flag = identify_quote(str[i], flag);
		if (flag)
			continue ;
		if (str[i] == '|' && !is_valid_pipe(str, i))
		{
			write(2, "bash: syntax error near unexpected token\n", 42);
			env->put(env, ft_strdup("?"), ft_strdup("2"));
			return (0);
		}
		else if ((str[i] == '<' || str[i] == '>') && !is_valid_redir(str, i))
		{
			write(2, "bash: syntax error near unexpected token\n", 42);
			env->put(env, ft_strdup("?"), ft_strdup("2"));
			return (0);
		}
	}
	return (1);
}
