/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:15 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/19 19:29:12 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_ns(char *arg)
{
	int	j;

	j = 1;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, t_exec *exec)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	while (cmd->args[i] && cmd->args[i][0] == '-' && only_ns(cmd->args[i]))
	{
		n_option = true;
		i++;
	}
	while (cmd->args[i])
	{
		write(exec->out, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(exec->out, " ", 1);
		i++;
	}
	if (!n_option)
		write(exec->out, "\n", 1);
	return (0);
}
