/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:10:15 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/24 17:18:31 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc_str(char *str, int len)
{
	char	*new;

	new = malloc(len);
	if (!new)
		return (free(str), NULL);
	if (str)
		ft_strlcpy(new, str, len);
	else
		new[0] = '\0';
	free(str);
	return (new);
}

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

t_cmd	*get_cmd_addr(t_cmd *src)
{
	static t_cmd	*cmd;

	if (src)
		cmd = src;
	return (cmd);
}

t_exec	*get_exec_addr(t_exec *src)
{
	static t_exec	*exec;

	if (src)
		exec = src;
	return (exec);
}
