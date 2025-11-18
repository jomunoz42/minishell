/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:39 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/18 20:38:34 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *str)
{
	bool	single_flag;
	bool	double_flag;
	int		i;
	t_map	*env;

	i = 0;
	single_flag = false;
	double_flag = false;
	env = get_map_addr(NULL);
	while (str[i])
	{
		if (str[i] == '"' && !single_flag)
			double_flag = !double_flag;
		else if (str[i] == '\'' && !double_flag)
			single_flag = !single_flag;
		i++;
	}
	if (single_flag || double_flag)
	{
		write(2, "bash: syntax error near unexpected token\n", 42);
		env->put(env, ft_strdup("?"), ft_strdup("2"));
		return (0);
	}
	return (1);
}

int	quote_handler(char *input, int n)
{
	int		i;
	char	flag;

	i = -1;
	flag = 0;
	if (!quote_count(input))
		return (0);
	while (input[++i])
	{
		flag = identify_quote(input[i], flag);
		if (!flag)
		{
			if (input[i] == '|' && n)
				input[i] = '\2';
			else if (input[i] == ' ')
				input[i] = '\3';
		}
	}
	return (1);
}

void	find_quotes(char *str, int i)
{
	int		j;
	char	quote;

	if (!str[i])
		return ;
	j = 0;
	if (str[i] == '"' || str[i] == '\'' || str[i] == '\3')
	{
		quote = str[i];
		j = i + 1;
		while (str[j] && str[j] != quote)
			j++;
		if (str[j] == quote)
		{
			ft_memmove(str + j, str + j + 1, ft_strlen(str + j + 1) + 1);
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			find_quotes(str, j - 1);
			return ;
		}
	}
	find_quotes(str, i + 1);
}

void	remove_quotes(t_cmd *head)
{
	int		i;
	t_cmd	*node;
	t_redir	*redir;

	node = head;
	while (node)
	{
		redir = node->redir;
		i = 0;
		while (node->args[i])
		{
			find_quotes(node->args[i], 0);
			i++;
		}
		while (redir)
		{
			find_quotes(redir->args[1], 0);
			redir = redir->next;
		}
		node = node->next;
	}
}

char	identify_quote(char c, char flag)
{
	if (c == '"' || c == '\'')
	{
		if (c == flag)
			return (0);
		else if (flag == 0)
			return (c);
	}
	return (flag);
}
