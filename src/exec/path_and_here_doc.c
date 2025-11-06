

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

	if (is_it_built_in(cmd))
		return (cmd);
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

int    exec_built_in(t_cmd *cmd, t_map *env, t_exec *exec)
{
    if (!cmd || !cmd->args)
	{
		env->put(env, "?", ft_strdup("0"));
        return (0);     
	}
    if (!ft_strncmp(cmd->args[0], "cd", 3))
        return (ft_cd(cmd, env));
    if (!ft_strncmp(cmd->args[0], "echo", 5))
        return (ft_echo(cmd, env, exec));
    if (!ft_strncmp(cmd->args[0], "pwd", 4))
        return (ft_pwd(env, exec));
    if (!ft_strncmp(cmd->args[0], "env", 4))
        return (ft_env(cmd, env, exec));
    if (!ft_strncmp(cmd->args[0], "export", 7))
        return (ft_export(cmd, env, exec));
    if (!ft_strncmp(cmd->args[0], "unset", 6))
       return (ft_unset(cmd, env));
	return (0);
}

static void	handling_here_doc(t_redir *redir, t_exec *exec)
{
	pid_t   pid;
	char	*line;
	int 	size;

	redir->fd = open("/tmp/mini_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (redir->fd == -1)
		handling_errors(exec, "/tmp/mini_temp", 1);
	pid = fork();
	if (pid == -1)
		handling_errors(exec, NULL, 4);
	if (!pid)
	{
		size = ft_strlen(redir->args[1]);
		while (1)
		{
			line = get_next_line(0);
			if (!line || !*line || ((ft_strncmp(redir->args[1], line, size) == 0)
					&& line[size] == '\n'))
			{
				free(line);
				break ;
			}
			(write(redir->fd, line, ft_strlen(line)), free(line));
		}
		(close(redir->fd), exit(0));
	}
	close(redir->fd);
}

void   execute_heredocs(t_cmd *cmd, t_exec *exec)
{
	t_cmd 	*cmd_temp;
	t_redir *redir_temp;

	cmd_temp = cmd;
	while(cmd_temp)
	{
		redir_temp = cmd_temp->redir;
		while(redir_temp)
		{
			if (ft_strncmp(redir_temp->args[0], "<<", 3) == 0)
			{
				handling_here_doc(redir_temp, exec);
				wait(NULL);
			}
			redir_temp = redir_temp->next;
		}
		cmd_temp = cmd_temp->next;
	}
}
