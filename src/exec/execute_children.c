
#include "minishell.h"

// static void	first_child(t_pipe *exec)
// {
// 	if (exec->only_one_cmd_exists == 1)
// 		return ;
// 	if (exec->child == 1)
// 	{
// 		if (exec->infile == -1)
// 		{
// 			close(exec->pipefd[0]);
// 			close(exec->pipefd[1]);
// 			if (exec->outfile != -1)
// 				close(exec->outfile);
// 			exit(126);
// 		}
// 		dup2(exec->out, 1);
// 		close(exec->out);
// 		dup2(exec->infile, 0);
// 		close(exec->infile);
// 		close(exec->pipefd[0]);
// 		if (exec->outfile != -1)
// 			close(exec->outfile);
// 	}
// }

// static void	middle_children(t_pipe *exec)
// {
// 	if (exec->child > 1 && exec->child < exec->cmd_number)
// 	{
// 		dup2(exec->in, 0);
// 		close(exec->in);
// 		dup2(exec->out, 1);
// 		close(exec->out);
// 		close(exec->pipefd[0]);
// 		if (exec->infile != -1)
// 			close(exec->infile);
// 		if (exec->outfile != -1)
// 			close(exec->outfile);
// 	}
// }

// static void	last_child(t_pipe *exec)
// {
// 	if (exec->only_one_cmd_exists == 1)
// 		return ;
// 	if (exec->child == exec->cmd_number)
// 	{
// 		if (exec->outfile == -1)
// 		{
// 			close(exec->pipefd[0]);
// 			close(exec->pipefd[1]);
// 			if (exec->infile != -1)
// 				close(exec->infile);
// 			exit(126);
// 		}
// 		dup2(exec->in, 0);
// 		close(exec->in);
// 		dup2(exec->outfile, 1);
// 		close(exec->outfile);
// 		close(exec->out);
// 		if (exec->infile != -1)
// 			close(exec->infile);
// 	}
// }

void	create_children(t_cmd *cmd, t_map *env, t_exec *exec, int i)
{

	char	*path;

	exec->process_id[i] = fork();
	if (!exec->process_id[i] == -1)
		// handling_errors(argv, exec, 4);
	if (exec->process_id[i] == 0)
	{
		dup2(exec->in, 0);
		close(exec->in);
		dup2(exec->out, 1);
		close(exec->out);
		if (exec->infile != -1)
			close(exec->infile);
		if (exec->outfile != -1)
			close(exec->outfile);
		path = get_absolute_path(env, cmd->args[0]);
		if (path)
			execve(path, cmd->args, env->to_str(env));
		handle_path_not_found(path, cmd);
	}
	if (!(exec->child == 1))
		close(exec->in);
	close(exec->out);
	exec->child++;
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)
{
	int i;

	i = 0;
	exec->cmd_number =  count_arguments(cmd->args);
	exec->process_id = malloc(sizeof(pid_t) * exec->cmd_number);
    if (!exec->process_id)
        ft_exit(1);
	exec->in = dup(0);
	while (i < exec->cmd_number)
	{
		exec->out = dup(1);
		// if (argv[exec->index + 2])
		// {
		// 	// if (pipe(exec->pipefd) == -1)
		// 	// 	handling_errors(argv, exec, 3);
		// 	pipe(exec->pipefd);
		// 	exec->out = exec->pipefd[1];
		// }
		create_children(cmd, env, exec, i);
		// exec->in = exec->pipefd[0];
		i++;
	}
	i = 1;
	while (i < exec->cmd_number)
		waitpid(exec->process_id[i++], NULL, 0);
	waitpid(exec->process_id[i], &exec->status, 0);
	free(exec->process_id);
}
