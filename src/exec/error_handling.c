
#include "minishell.h"

// void	handling_errors(char **argv, t_pipe *get, int error_id)
// {
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
// 	if (error_id == 3)
// 	{
// 		perror("Error opening pipe");
// 		close_everything(get);
// 		exit(1);
// 	}
// 	if (error_id == 4)
// 	{
// 		perror("Error creating fork");
// 		close_everything(get);
// 		exit(1);
// 	}
// }

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

// void	close_everything(t_pipe *get)
// {
// 	if (get->infile != -1)
// 		close(get->infile);
// 	if (get->outfile != -1)
// 		close(get->outfile);
// 	if (get->pipefd[0] != -1)
// 		close(get->pipefd[0]);
// 	if (get->pipefd[1] != -1)
// 		close(get->pipefd[1]);
// } 