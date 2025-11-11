
#include "minishell.h"

int   is_there_slash(char *path);

void	handling_errors(t_exec *exec, char *arg, int error_id, t_cmd *cmd)
{
	if (error_id == 1)
		(write(2, "bash: ", 6), perror(arg));
	if (error_id == 2)
		(write(2, "bash: ", 6), perror(arg));
	if (errno == ENOENT) 
		exec->no_file = true;
	else if (errno == EACCES)
		exec->no_permission = true; ///  chekar  testar -x de um ficheiro
	if (error_id == 3)
	{
		perror("pipe");
		close_everything(exec); // check
		ft_exit(1, exec, cmd);                // free everything
	}
	if (error_id == 4)
	{
		perror("fork");
		close_everything(exec); // check
		ft_exit(1, exec, cmd);                // free everything
	}
}

static void	 error_messages(char *path)
{
	struct stat buf;
    
	write(2, "bash: ", 6);
	write(2, path, ft_strlen(path));
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
        {
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
    }
    else if (S_ISREG(buf.st_mode))
    {
		write(2, ": Permission denied\n", 21);
		exit(126);
	}
    else if (S_ISDIR(buf.st_mode))
	{
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
}

void	handle_execve_errors(t_cmd *cmd, t_map *env, t_exec *exec)
{
	if (is_there_slash(cmd->args[0]))
		error_messages(cmd->args[0]);
	else
	{
		if (env->get(env, "PATH") == NULL || env->get(env, "PATH")[0] == '\0')
		{
			write(2, "bash: ", 6);
			perror(cmd->args[0]);
		}
		else
		{
			if (cmd->args[0] && ft_strncmp(cmd->args[0], "", 1) == 0)
			{
				write(2, "Command '' not found\n", 22);
				ft_exit(127, exec, cmd);                    // check this for leaks
			}
			else
			{
				write(2, cmd->args[0], ft_strlen(cmd->args[0]));
				write(2, ": command not found\n", 21);
			}
		}
		if (cmd->args[0] && cmd->args[0][0] != '\0')
			free(cmd->args[0]);
		free_double(cmd->args);
		ft_exit(127, exec, cmd);
	}
}

void	close_everything(t_exec *exec)
{
	if (exec->in != -1)
		close(exec->in);
	if (exec->out != -1)
		close(exec->out);
	// falta aqui if (pipefd[0] > 0) e (pipefd[1] > 0)
} 

void close_and_reset(t_exec *exec)
{
	if (exec->in)
		close(exec->in);
	if (exec->out)
		close(exec->out);
	exec->no_file = false;
	exec->no_permission = false;
}
