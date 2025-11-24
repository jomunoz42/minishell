/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:02:58 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/24 18:54:40 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirections_util2(t_redir *temp, t_exec *exec, t_cmd *cmd)
{
	if (ft_strncmp(temp->args[0], ">>", 3) == 0)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->out == -1)
		{
			if (handling_errors(exec, temp->args[1], 2, cmd))
				return (1);
		}
	}
	if (ft_strncmp(temp->args[0], ">", 2) == 0)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->out == -1)
		{
			if (handling_errors(exec, temp->args[1], 2, cmd))
				return (1);
		}
	}
	return (0);
}

static int	redirections_util1(t_redir *temp, t_exec *exec, t_cmd *cmd)
{
	if (ft_strncmp(temp->args[0], "<", 2) == 0)
	{
		((exec->in > 2) && close(exec->in));
		exec->in = open(temp->args[1], O_RDONLY);
		if (exec->in == -1)
		{
			if (handling_errors(exec, temp->args[1], 1, cmd))
				return (1);
		}
	}
	return (0);
}

void	redirections(t_redir *redir, t_exec *exec, t_cmd *cmd)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (ft_strncmp(temp->args[0], "<<", 3) == 0)
		{
			((exec->in > 2) && close(exec->in));
			exec->in = temp->fd;
		}
		if (redirections_util1(temp, exec, cmd))
			return ;
		if (redirections_util2(temp, exec, cmd))
			return ;
		temp = temp->next;
	}
}
