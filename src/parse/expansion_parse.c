/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:04 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/23 20:17:51 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		split_expansion_helper(t_cmd *node, int i);
char	*expanded_arg(char *str, t_map *env, int n);
void	free_list(t_cmd *all);
int		expand_redir(t_cmd *head);

int	organize_args(char **args, t_cmd *node, t_cmd *head)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if ((!*args[i] || (*args[i] == '\2' && ft_strlen(args[i]) == 1))
			&& args[i + 1])
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
	if (node->redir)
		return (1);
	if (!*args[0] || (*args[0] == '\2' && ft_strlen(args[0]) == 1))
		return (free_list(head), 0);
	return (1);
}

char	*pseudo_quotes(char *splited)
{
	int		len;
	char	*str;

	len = ft_strlen(splited);
	str = ft_calloc(len + 4, 1);
	if (!str)
		return (NULL);
	if (splited[0] == '\2')
	{
		splited++;
		len--;
	}
	str[0] = '\3';
	ft_memcpy(str + 1, splited, len);
	str[len + 1] = '\3';
	str[len + 2] = 0;
	return (str);
}

int	split_expansion(t_cmd *head)
{
	int		i;
	t_cmd	*node;

	node = head;
	while (node)
	{
		i = -1;
		while (node->args[++i])
		{
			quote_handler(node->args[i], 0);
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
		if (!node->args)
			return (0);
		if (!organize_args(node->args, node, head))
			return (0);
		node = node->next;
	}
	return (1);
}

int	change_expansion(t_cmd *head)
{
	int		i;
	t_cmd	*node;
	t_map	*env;

	node = head;
	env = get_map_addr(NULL);
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			node->args[i] = expanded_arg(node->args[i], env, 1);
			if (!node->args[i])
				return (0);
			i++;
		}
		node = node->next;
	}
	if (!organize_list(head) || !split_expansion(head) || !expand_redir(head))
		return (0);
	return (1);
}
