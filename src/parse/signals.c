/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:29 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/25 18:22:48 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_exit(t_cmd *cmd)
{
	t_redir	*redir;
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		redir = temp->redir;
		while (redir)
		{
			if (redir && redir->fd > 2)
				close(redir->fd);
			redir = redir->next;
		}
		temp = temp->next;
	}
}

void	sig_heredoc_handler(int sig)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	t_exec	*exec;

	(void)sig;
	cmd = get_cmd_addr(NULL);
	exec = get_exec_addr(NULL);
	temp = cmd;
	close_everything(exec);
	close_fds_exit(temp);
	write(1, "\n", 1);
	ft_exit(130, exec, cmd);
}

void	handler(int sig)
{
	t_map	*env;

	(void)sig;
	env = get_map_addr(NULL);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	env->put(env, ft_strdup("?"), ft_strdup("130"));
}

void	sig_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}

void	put_error_msg(void)
{
	t_map	*env;

	env = get_map_addr(NULL);
	write(2, "bash: syntax error near unexpected token\n", 42);
	env->put(env, ft_strdup("?"), ft_strdup("2"));
}
