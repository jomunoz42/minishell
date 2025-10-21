

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
// 	}
// }

void	handling_here_doc(t_cmd *cmd, t_exec *exec)
{
	char	*line;
	int 	size;

	size = ft_strlen(cmd->redir->args[1]);
	while (1)
	{
		line = get_next_line(0);
		// ctrl_d_pressed(argv, get, line);
		// if (exec->eof_no_limiter == 1)
		// 	break ;
		if (!*line || ((ft_strncmp(cmd->redir->args[1], line, size) == 0)
				&& line[size] == '\n'))
		{
			free(line);
			break ;
		}
		write(cmd->redir->fd, &line, ft_strlen(line));
		free(line);
	}
}
