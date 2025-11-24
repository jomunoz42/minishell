/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:12 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/24 22:17:08 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pseudo_quotes(char *splited);
int		check_size(char *str);
char	*expanded_arg(char *str, t_map *env, int n);
void	free_list(t_cmd *all);
void	expand_heredoc(char *str);

char	**new_args_expanded(char **splited, t_cmd *node, int start)
{
	int		j;
	int		i;
	int		size;
	char	**new_args;

	size = arr_count(node->args) + arr_count(splited);
	new_args = ft_calloc(size + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		if (i == start)
		{
			j = -1;
			while (++j < arr_count(splited))
				new_args[i + j] = pseudo_quotes(splited[j]);
			i = i + j;
			continue ;
		}
		else
			new_args[i] = ft_strdup(node->args[i]);
		i++;
	}
	return (new_args);
}

int	split_expansion_helper(t_cmd *node, int i)
{
	char	**splited;
	char	**tmp_double;

	splited = ft_split(node->args[i], '\3');
	if (!splited)
		return (0);
	if (arr_count(splited) > 1)
	{
		tmp_double = node->args;
		node->args = new_args_expanded(splited, node, i);
		free_double(tmp_double);
		if (!node->args)
			return (free_double(splited), 0);
	}
	free_double(splited);
	return (1);
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

int	expand_redir_helper(t_redir *redir, t_map *env, t_cmd *head)
{
	char	*temp;

	while (redir)
	{
		if (!strncmp(redir->args[0], "<<", 3))
			expand_heredoc(redir->args[1]);
		else
		{
			temp = expanded_arg(redir->args[1], env, 0);
			if (!temp)
			{
				write(2, "Allocation error\n", 17);
				return (free_list(head), 0);
			}
			redir->args[1] = temp;
			if (!*redir->args[1])
			{
				write(2, "bash: ambiguous redirect\n", 25);
				return (free_list(head), 0);
			}
		}
		redir = redir->next;
	}
	return (1);
}

int	expand_redir(t_cmd *head)
{
	t_cmd	*node;
	t_map	*env;
	t_redir	*redir;

	node = head;
	env = get_map_addr(NULL);
	while (node)
	{
		redir = node->redir;
		if (!expand_redir_helper(redir, env, head))
			return (0);
		node = node->next;
	}
	return (1);
}
