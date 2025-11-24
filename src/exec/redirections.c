/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:02:58 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/24 20:57:18 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirections_out(t_redir *temp, t_exec *exec, t_cmd *cmd)
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

static int	redirections_in(t_redir *temp, t_exec *exec, t_cmd *cmd)
{
	if (ft_strncmp(temp->args[0], "<", 2) == 0)
	{
		if (exec->in > 2)
			close(exec->in);
		exec->in = open(temp->args[1], O_RDONLY);
		if (exec->in == -1 && handling_errors(exec, temp->args[1], 1, cmd))
			return (1);
	} 
	else if (ft_strncmp(temp->args[0], "<<", 3) == 0)
	{
			if (exec->in > 2)
				close(exec->in);
			exec->in = temp->fd;
	}
	return (0);
}

void	redirections(t_redir *redir, t_exec *exec, t_cmd *cmd)
{
	t_redir	*temp;
	t_redir	*prev_in;
	t_redir	*prev_out;

	temp = redir;
	prev_in = NULL;
	prev_out = NULL;
	while (temp)
	{
		if (redirections_in(temp, exec, cmd))
			return ;
		if (redirections_out(temp, exec, cmd))
			return ;
		temp = temp->next;
	}
}
