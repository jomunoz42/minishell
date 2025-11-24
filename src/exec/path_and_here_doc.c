/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:01 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/24 19:11:49 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_heredoc_handler(int sig);
void		print_env(t_map *env);
int			is_it_built_in(char *cmd);
char		*get_path_dir(char *str, char *cmd);
char		*expanded_arg(char *str, t_map *env, int n);

char	*get_absolute_path(t_map *env, char *cmd)
{
	char	*temp;
	char	*str;

	if (!cmd)
		return (NULL);
	if (!*cmd || is_it_built_in(cmd) || access(cmd, X_OK) == 0)
		return (cmd);
	str = env->get(env, "PATH");
	if (!str || str[0] == '\0')
		return (cmd);
	temp = get_path_dir(str, cmd);
	return (temp);
}

static int	here_doc_util(t_redir *redir, char *line, int size, t_exec *exec)
{
	t_map	*env;
	char	*temp;

	if (!line || !*line || ft_strncmp(redir->args[1], line, size + 1) == 0)
		return (free(line), 1);
	env = get_map_addr(NULL);
	if (exec->expand)
	{
		temp = expanded_arg(line, env, 0);
		if (!temp)
			return (1);
		line = temp;
	}
	(write(redir->fd, line, ft_strlen(line)), free(line));
	write(redir->fd, "\n", 1);
	return (0);
}

static void	handling_here_doc(t_redir *redir, t_exec *exec, t_cmd *cmd)
{
	pid_t	pid;
	char	*line;
	int		size;

	pid = fork();
	if (pid == -1)
		handling_errors(exec, NULL, 4, cmd);
	if (!pid)
	{
		redir->fd = open("/tmp/mini_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (redir->fd == -1)
			(handling_errors(exec, "/tmp/mini_temp", 1, cmd), ft_exit(1, exec,
					cmd));
		exec->is_child = true;
		(signal(SIGINT, sig_heredoc_handler), signal(SIGQUIT, SIG_IGN));
		size = ft_strlen(redir->args[1]);
		while (1)
		{
			line = readline("> ");
			if (here_doc_util(redir, line, size, exec))
				break ;
		}
		close(redir->fd);
		ft_exit(0, exec, cmd);
	}
}

int	exec_heredocs(t_cmd *cmd, t_cmd *temp, t_exec *exec, t_map *env)
{
	t_cmd	*cmd_temp;
	t_redir	*redir_temp;
	int		s;

	cmd_temp = temp;
	while (cmd_temp)
	{
		redir_temp = cmd_temp->redir;
		while (redir_temp)
		{
			if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
			{
				handling_here_doc(redir_temp, exec, cmd);
				wait(&s);
				redir_temp->fd = open("/tmp/mini_temp", O_RDONLY);
				unlink("/tmp/mini_temp");
				s = convert_status(s);
				if (s)
					return (env->put(env, ft_strdup("?"), ft_itoa(s)), s);
			}
			redir_temp = redir_temp->next;
		}
		cmd_temp = cmd_temp->next;
	}
	return (0);
}

int	convert_status(int status)
{
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		status += 128;
	}
	else
	{
		status = 1;
	}
	return (status);
}
