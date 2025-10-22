

#include "minishell.h"

char	*get_absolute_path(t_map *env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*temp;
	char	*str;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	str = env->get(env, "PATH");
	if (!str || str[0] == '\0')
		return (cmd);
	i = -1;
	dirs = ft_split(str, ':');
	while (dirs[++i])
	{
		temp = ft_strjoin_free(dirs[i], "/");
		path = ft_strjoin_free(temp, cmd);
		if (access(path, X_OK) == 0)
			return (free(cmd), path);
		free(path);
	}
	return (cmd);
}

// static void	ctrl_d_pressed(t_cmd *cmd, char **argv, char *line)
// {
// 	if (!line)
// 	{
// 		write(2,
// 			"bash: warning: here-document delimited by end-of-file (wanted `",
// 			63);
// 		write(2, argv[2], get->length);
// 		write(2, "')\n", 3);
// 		close(get->hdoc_pipe[1]);
// 		get->infile = get->hdoc_pipe[0];
// 		get->eof_no_limiter = 1;
						// ctrl_d_pressed(argv, get, line);
						// if (exec->eof_no_limiter == 1)
						// 	break ;
// 	}
// }

static void	handling_here_doc(t_redir *redir_temp, t_exec *exec)
{
	pid_t   pid;
	char	*line;
	int 	size;

	redir_temp->fd = open(redir_temp->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->in == -1)
		handling_errors(exec, redir_temp->args[1], 1);
	pid = fork();
	if (pid == -1)
		handling_errors(exec, NULL, 4);
	if (!pid)
	{
		size = ft_strlen(redir_temp->args[1]);
		while (1)
		{
			line = get_next_line(0);
			if (!line || !*line || ((ft_strncmp(redir_temp->args[1], line, size) == 0)
					&& line[size] == '\n'))
			{
				free(line);
				break ;
			}
			write(redir_temp->fd, line, ft_strlen(line));
			free(line);
		}
		close(redir_temp->fd);
		exit(0);
	}
}

static int true_last_here_doc(t_cmd *cmd_temp)
{
	t_redir *redir_temp;

	redir_temp = cmd_temp->redir;
	while(cmd_temp)
	{
		while(redir_temp)
		{
			if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
				return (0);
			redir_temp = redir_temp->next;
		}
		cmd_temp = cmd_temp->next;
	}
	return (1);
}

static void   mark_last_heredoc(t_cmd *cmd_temp, t_exec *exec, int marker)
{
	t_redir *redir_temp;

	redir_temp = cmd_temp->redir;
	while(redir_temp)
	{
		if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
			marker--;
		if (marker == 0)
		{
			if (true_last_here_doc(cmd_temp))
				redir_temp->last_here_doc = 2;
			else
				redir_temp->last_here_doc = 1;
		}
		redir_temp = redir_temp->next;
	}
}

void   execute_heredocs(t_cmd *cmd, t_exec *exec)
{
	t_cmd 	*cmd_temp;
	t_redir *redir_temp;
	int   marker;

	cmd_temp = cmd;
	while(cmd_temp)
	{
		marker = 0;
		redir_temp = cmd_temp->redir;
		while(redir_temp)
		{
			if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
			{
				handling_here_doc(redir_temp, exec);
				wait(NULL);
				redir_temp->last_here_doc = 0;
				marker++;
			}
			redir_temp = redir_temp->next;
		}
		mark_last_heredoc(cmd_temp, exec, marker);
		cmd_temp = cmd_temp->next;
	}
}



// HERE DOC DOESN'T WRITE TO THE LAST INFILE IF THERE IS MORE THAN ONE.