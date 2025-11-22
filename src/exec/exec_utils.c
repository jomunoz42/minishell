/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:04 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/21 21:42:49 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(t_map *env, char *cmd);

int	is_it_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else
		return (0);
}

int	exec_built_in(t_cmd *cmd, t_map *env, t_exec *exec)
{
	int	status;

	status = 0;
	if (!cmd || !cmd->args)
		return (status);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		status = ft_cd(cmd, env);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		status = ft_echo(cmd, exec);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		status = ft_pwd(env, exec);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		status = ft_env(cmd, env, exec);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		status = ft_export(cmd, env, exec);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		status = ft_unset(cmd, env);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
	{
		if (cmd->args[1])
			status = exit_parsing(cmd, exec, env);
		else
			ft_exit(ft_atoi(env->get(env, "?")), exec, cmd);
	}
	return (env->put(env, ft_strdup("?"), ft_itoa(status)), status);
}

void	handle_built_in(t_cmd *head, t_cmd *temp, t_map *env, t_exec *exec)
{
	int	status;

	if (is_it_built_in(temp->args[0]))
	{
		status = exec_built_in(temp, env, exec);
		if (exec->in > 2)
			close(exec->in);
		if (exec->out > 2)
			close(exec->out);
		if (exec->pipefd[0])
			close(exec->pipefd[0]);
		ft_exit(status, exec, head);
	}
	else
		temp->args[0] = get_absolute_path(env, temp->args[0]);
}

int	is_parent_built_ins(t_cmd *temp, t_map *env, t_exec *exec)
{
	int	invalid;

	exec->in = -1;
	exec->out = -1;
	if (!temp->next && is_it_built_in(temp->args[0]))
	{
		exec->out = dup(1);
		redirections(temp->redir, exec, temp);
		invalid = no_file_no_perm(temp, exec);
		if (invalid)
			return (1);
		exec_built_in(temp, env, exec);
		if (exec->in > 2)
			close(exec->in);
		if (exec->out > 2)
			close(exec->out);
		return (1);
	}
	return (0);
}

int	no_file_no_perm(t_cmd *cmd, t_exec *exec)
{
	t_map	*env;

	env = get_map_addr(NULL);
	if (!exec->is_child && (exec->no_file || exec->no_permission))
	{
		close_and_reset(exec);
		env->put(env, ft_strdup("?"), ft_strdup("1"));
		if (exec->out > 2)
			close(exec->out);
		if (exec->in > 2)
			close(exec->in);
		return (1);
	}
	if (exec->no_file || exec->no_permission)
	{
		if (exec->out > 2)
			close(exec->out);
		if (exec->in > 2)
			close(exec->in);
		if (exec->pipefd[0])
			close(exec->pipefd[0]);
		ft_exit(1, exec, cmd);
	}
	return (0);
}
