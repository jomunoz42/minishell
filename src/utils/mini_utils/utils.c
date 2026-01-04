/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:09:45 by pbongiov          #+#    #+#             */
/*   Updated: 2026/01/04 21:49:29 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr(const char *s, int c);

void	free_double(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return ;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*find_last_slash(char *current_pwd)
{
	char	*last_slash;

	last_slash = ft_strrchr(current_pwd, '/');
	if (last_slash)
	{
		if (last_slash == current_pwd)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
	}
	return (current_pwd);
}

int	get_pid(t_exec *exec, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		exec->is_child = true;
		ft_exit(0, exec, cmd);
	}
	wait(NULL);
	return (pid - 1);
}
