/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:21 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/23 15:41:45 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_sintax(char *str);

int	remove_redir(t_cmd *head, int i)
{
	int	len;

	len = arr_count(head->args);
	free(head->args[i]);
	free(head->args[i + 1]);
	ft_memmove(&head->args[i], &head->args[i + 2], (len - i - 1)
		* sizeof(char *));
	return (1);
}

int	is_empty(char *input)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (input[i])
	{
		if (input[i++] != ' ')
		{
			flag = true;
			break ;
		}
	}
	return (flag == true);
}

char	*primary_check(char *input)
{
	char	*dup;

	if (!input || !is_empty(input))
		return (NULL);
	if (!check_sintax(input) || !quote_handler(input, 1))
		return (NULL);
	dup = ft_strdup(input);
	if (!dup)
		return (NULL);
	dup = unlink_redir(dup);
	if (!dup)
		return (NULL);
	return (dup);
}

t_cmd	*parsing(char *input, t_cmd *head)
{
	int		i;
	char	**line;

	input = primary_check(input);
	if (!input)
		return (NULL);
	line = ft_split(input, '\2');
	if (!line)
		return (perror("Allocation Error"), NULL);
	i = 0;
	while (line[i])
	{
		head = separate_args(head, line[i]);
		if (!head)
			return (free_double(line), NULL);
		i++;
	}
	free(input);
	free_double(line);
	if (!init_redir(head))
		return (NULL);
	if (!change_expansion(head))
		return (NULL);
	remove_quotes(head);
	return (head);
}
