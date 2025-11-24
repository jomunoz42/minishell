/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:03:31 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/24 18:04:24 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count(char *str);

int	expand_heredoc(char *str)
{
	int		i;
	t_exec	*exec;

	i = 0;
	exec = get_exec_addr(NULL);
	if (!quote_count(str))
		return (0);
	exec->expand = true;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			exec->expand = false;
			break ;
		}
		i++;
	}
	return (1);
}

int	is_valid_pipe_util(char *str)
{
	int		i;
	char	last_char;

	i = -1;
	last_char = 0;
	while (str[++i])
	{
		if (str[i] != ' ')
			last_char = str[i];
	}
	if (last_char == '|')
		return (0);
	return (1);
}
