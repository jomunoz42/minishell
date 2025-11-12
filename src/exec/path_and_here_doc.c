

#include "minishell.h"

void				print_env(t_map *env);
int				    is_it_built_in(char *cmd);

char	*get_absolute_path(t_map *env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*temp;
	char	*str;
	int		i;

	if (!*cmd)
		return ("");
	if (is_it_built_in(cmd) || access(cmd, X_OK) == 0)
		return (cmd);
	str = env->get(env, "PATH");
	if (!str || str[0] == '\0')
		return (cmd);
	i = -1;
	dirs = ft_split(str, ':');
	if (!dirs)
		return (NULL);
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin_free(temp, cmd);
		if (access(path, X_OK) == 0)
			return (free_double(dirs), path);
		free(path);
	}
	free_double(dirs);
	return (cmd);
}

static int	here_doc_util(t_redir *redir, char *line, int size)
{
	if (!line || !*line || ((ft_strncmp(redir->args[1], line, size) == 0)
			&& line[size] == '\n'))
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	handling_here_doc(t_redir *redir, t_exec *exec, t_cmd *cmd)
{
	pid_t   pid;
	char	*line;
	int 	size;

	redir->fd = open("/tmp/mini_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (redir->fd == -1)
		handling_errors(exec, "/tmp/mini_temp", 1, cmd);
	pid = fork();
	if (pid == -1)
		handling_errors(exec, NULL, 4, cmd);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		size = ft_strlen(redir->args[1]);
		while (1)
		{
			line = get_next_line(0);
			if (here_doc_util(redir, line, size))
				break ;
			(write(redir->fd, line, ft_strlen(line)), free(line));
		}
		(close(redir->fd), ft_exit(0, exec, cmd));
	}
	close(redir->fd);
}

int   execute_heredocs(t_cmd *cmd, t_exec *exec)
{
	t_cmd 	*cmd_temp;
	t_redir *redir_temp;
	int		status;

	cmd_temp = cmd;
	while(cmd_temp)
	{
		redir_temp = cmd_temp->redir;
		while(redir_temp)
		{
			if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
			{
				handling_here_doc(redir_temp, exec, cmd_temp);
				wait(&status);
				status = convert_status(status);
				if (status)
					return (1);
			}
			redir_temp = redir_temp->next;
		}
		cmd_temp = cmd_temp->next;
	}
	return (0);
}

int convert_status(int status)
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