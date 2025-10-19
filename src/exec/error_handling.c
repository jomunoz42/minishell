
#include "minishell.h"

void	handling_errors(t_cmd *cmd, t_exec *exec, int error_id)
{
// 	if (error_id == 1)
// 	{
// 		write(2, "bash: ", 6);
// 		perror(argv[1]);
// 	}
// 	if (error_id == 2)
// 	{
// 		write(2, "bash: ", 6);
// 		perror(argv[get->last_arg]);
// 	}
	if (error_id == 3)
	{
		perror("pipe");
		close_everything(exec);
		exit(1);
	}
	if (error_id == 4)
	{
		perror("fork");
		close_everything(exec);
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
	if (exec->infile != -1)
		close(exec->infile);
	if (exec->outfile != -1)
		close(exec->outfile);
	if (exec->pipefd[0] != -1)
		close(exec->pipefd[0]);
	if (exec->pipefd[1] != -1)
		close(exec->pipefd[1]);
} 