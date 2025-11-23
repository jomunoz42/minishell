/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:07 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/23 17:37:20 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_there_slash(char *path);

int	handling_errors(t_exec *exec, char *arg, int error_id, t_cmd *cmd)
{
	t_map	*env;

	env = get_map_addr(NULL);
	if (errno == ENOENT || errno == EISDIR)
		exec->no_file = true;
	else if (errno == EACCES)
		exec->no_permission = true;
	if (error_id == 1)
	{
		(write(2, "bash: ", 6), perror(arg));
		env->put(env, ft_strdup("?"), ft_strdup("1"));
		return (1);
	}
	if (error_id == 2)
	{
		(write(2, "bash: ", 6), perror(arg));
		return (env->put(env, ft_strdup("?"), ft_strdup("1")), 1);
	}
	if (error_id == 3)
		(perror("pipe"), (close_everything(exec), ft_exit(1, exec, cmd)));
	if (error_id == 4)
		(perror("fork"), (close_everything(exec), ft_exit(1, exec, cmd)));
	return (0);
}

static void	error_messages(char *path, t_exec *exec, t_cmd *cmd)
{
	struct stat	buf;

	write(2, "bash: ", 6);
	write(2, path, ft_strlen(path));
	if (stat(path, &buf) != 0)
	{
		if (errno == ENOENT)
		{
			write(2, ": No such file or directory\n", 29);
			ft_exit(127, exec, cmd);
		}
	}
	else if (S_ISREG(buf.st_mode))
	{
		write(2, ": Permission denied\n", 21);
		ft_exit(126, exec, cmd);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		write(2, ": Is a directory\n", 18);
		ft_exit(126, exec, cmd);
	}
}

void	handle_execve_errors(t_cmd *cmd, t_cmd *temp, t_map *env, t_exec *exec)
{
	(!cmd->args[0] && cmd->redir) && (ft_exit(0, exec, cmd));
	if (is_there_slash(temp->args[0]))
		error_messages(temp->args[0], exec, cmd);
	else
	{
		if (env->get(env, "PATH") == NULL || env->get(env, "PATH")[0] == '\0')
		{
			write(2, "bash: ", 6);
			perror(temp->args[0]);
		}
		else
		{
			if (temp->args[0] && ft_strncmp(temp->args[0], "", 1) == 0)
			{
				write(2, "Command '' not found\n", 22);
				ft_exit(127, exec, cmd);
			}
			else
			{
				write(2, temp->args[0], ft_strlen(temp->args[0]));
				write(2, ": command not found\n", 21);
			}
		}
		ft_exit(127, exec, cmd);
	}
}

void	close_everything(t_exec *exec)
{
	if (exec->in > 2)
		close(exec->in);
	if (exec->out > 2)
		close(exec->out);
	if (exec->pipefd[0] > 2)
		close(exec->pipefd[0]);
	if (exec->pipefd[1] > 2)
		close(exec->pipefd[1]);
}

void	close_and_reset(t_exec *exec)
{
	if (exec->in > 2)
		close(exec->in);
	if (exec->out > 2)
		close(exec->out);
	exec->no_file = false;
	exec->no_permission = false;
}
