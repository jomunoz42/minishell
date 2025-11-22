/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:29 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/22 19:24:02 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds_exit(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir && redir->fd > 2)
				close(redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
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
