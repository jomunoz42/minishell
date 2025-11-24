/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:20:57 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/24 21:51:39 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_it_built_in(char *cmd);
int			exec_built_in(t_cmd *cmd, t_map *env, t_exec *exec);
int			parent_built_in(t_cmd *temp, t_map *env, t_exec *exec);
void		handle_built_in(t_cmd *cmd, t_cmd *temp, t_map *env, t_exec *exec);

static void	waiting_proccesses(t_cmd *cmd, t_exec *exec, t_map *env)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		waitpid(temp->pid, &exec->status, 0);
		temp = temp->next;
	}
	exec->status = convert_status(exec->status);
	env->put(env, ft_strdup("?"), ft_itoa(exec->status));
}

static void	create_children(t_cmd *cmd, t_cmd *temp, t_map *env, t_exec *exec)
{
	temp->pid = fork();
	if (temp->pid == -1)
		handling_errors(exec, NULL, 4, cmd);
	if (!temp->pid)
	{
		exec->is_child = true;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		no_file_no_perm(cmd, exec);
		handle_built_in(cmd, temp, env, exec);
		dup2(exec->in, 0);
		if (exec->in > 2)
			close(exec->in);
		dup2(exec->out, 1);
		if (exec->out > 2)
			close(exec->out);
		if (exec->pipefd[0])
			close(exec->pipefd[0]);
		if (!temp->args[0])
			ft_exit(1, exec, cmd);
		execve(temp->args[0], temp->args, env->to_str(env));
		handle_execve_errors(cmd, temp, env, exec);
	}
	close_and_reset(exec, temp);
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)
{
	t_cmd	*temp;

	temp = cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	get_cmd_addr(cmd);
	if (exec_heredocs(cmd, temp, exec, env) || parent_built_in(temp, env, exec))
		return ;
	exec->in = dup(STDIN_FILENO);
	while (temp)
	{
		exec->out = dup(STDOUT_FILENO);
		if (temp->next)
		{
			if (pipe(exec->pipefd) == -1)
				handling_errors(exec, NULL, 3, cmd);
			close(exec->out);
			exec->out = exec->pipefd[1];
		}
		redirections(temp->redir, exec, cmd);
		create_children(cmd, temp, env, exec);
		exec->in = exec->pipefd[0];
		temp = temp->next;
	}
	waiting_proccesses(cmd, exec, env);
}
