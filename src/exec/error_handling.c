
#include "minishell.h"

void	handling_errors(t_exec *exec, char *arg, int error_id)
{
	if (error_id == 1)
	{
		write(2, "bash: ", 6);
		perror(arg);            // check
	}
	if (error_id == 2)
	{
		write(2, "bash: ", 6);
		perror(arg); 			// check
	}
	if (error_id == 3)
	{
		perror("pipe");
		close_everything(exec); // check
		exit(1);
	}
	if (error_id == 4)
	{
		perror("fork");
		close_everything(exec); // check
		exit(1);
	}
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (path && ft_strncmp(path, "", 1) == 0)
		write(2, "''", 2);
	else
		write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
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