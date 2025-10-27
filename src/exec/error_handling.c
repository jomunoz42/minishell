
#include "minishell.h"

void	handling_errors(t_exec *exec, char *arg, int error_id)
{
	if (error_id == 1)
	{
		write(2, "bash: ", 6);
		perror(arg);
	}
	if (error_id == 2)
	{
		write(2, "bash: ", 6);
		perror(arg);
	}
	if (errno == ENOENT) 
		exec->no_file = true;
	else if (errno == EACCES)
		exec->no_permission = true;
	if (error_id == 3)
	{
		perror("pipe");
		close_everything(exec); // check
		exit(1);                // free everything
	}
	if (error_id == 4)
	{
		perror("fork");
		close_everything(exec); // check
		exit(1);                // free everything
	}
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (path && ft_strncmp(path, "\"\"", 1) == 0)
		write(2, "Command '' not found\n", 22);
	else
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 21);
	}
	if (path && path != cmd[0] && path[0] != '\0')
		free(path);
	free_double(cmd);
	exit(127);
}

void	close_everything(t_exec *exec)
{
	if (exec->in != -1)
		close(exec->in);
	if (exec->out != -1)
		close(exec->out);
} 