
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



// static void infile_and_outfile(t_cmd *cmd, t_exec *exec)
// {
// 	exec->infile = open(      , O_RDONLY);
// 	if (exec->infile == -1)
// 		// handling_errors(      , exec, 1);
// 	exec->outfile = open(, O_CREAT | O_WRONLY | O_TRUNC,
// 			0644);
// 	if (exec->outfile == -1)
// 		// handling_errors(     , exec, 2);
// }

static void waiting_proccesses(t_exec *exec, t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			waitpid(cmd->pid, &exec->status, 0);
		else
			waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
}

static void redirections(t_cmd *cmd, t_map *env, t_exec *exec)
{
	if (ft_strncmp(cmd->redir->args[0], "<<", 3) == 0)
	{
		exec->in = cmd->redir->fd;
		// close ??
	}
	if (ft_strncmp(cmd->redir->args[0], "<", 2) == 0)
	{
		exec->in = open(cmd->redir->args[1], O_RDONLY);
		if (exec->in == -1)
			handling_errors(exec, cmd->redir->args[1], 1);
	}
	if (ft_strncmp(cmd->redir->args[0], ">>", 3) == 0)
	{
		exec->out = open(cmd->redir->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->out == -1)
			handling_errors(exec, cmd->redir->args[1], 2);
	}
	if (ft_strncmp(cmd->redir->args[0], ">", 2) == 0)
	{
		exec->out = open(cmd->redir->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->out == -1)
			handling_errors(exec, cmd->redir->args[1], 2);
	}
}

void	create_children(t_cmd *cmd, t_map *env, t_exec *exec)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		handling_errors(exec, NULL, 4);
	if (cmd->pid == 0)
	{
	
		dup2(exec->in, 0);
		close(exec->in);
		dup2(exec->out, 1);
		close(exec->out);
		// if (exec->pipefd[0])
		// 	close(exec->pipefd[0]);
		// if (exec->infile != -1)
		// 	close(exec->infile);
		// if (exec->outfile != -1)
		// 	close(exec->outfile);
		execve(cmd->args[0], cmd->args, env->to_str(env));
		// handle_path_not_found(cmd->args[0], cmd->args);
	}
	if (exec->in)
		close(exec->in);
	if (exec->out)
		close(exec->out);
}

void   run_all_heredocs(t_cmd *cmd, t_exec *exec)
{
	t_cmd *temp;
	int   marker;

	marker = 0;
	temp = cmd;
	while(temp)
	{
		if (ft_strncmp(temp->redir->args[0], "<<", 3) == 0)
		{
			handling_here_doc(temp, exec);
			temp->redir->last_here_doc = false;
			marker++;
		}
		temp = temp->next;
	}
	temp = cmd;
	while(temp)
	{
		if (ft_strncmp(temp->redir->args[0], "<<", 3) == 0)
			marker--;
		if (marker == 0)
			temp->redir->last_here_doc = true;
		temp = temp->next;
	}
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)  // env ??
{
	t_cmd *temp;

	temp = cmd;
	run_all_heredocs(cmd, exec);
	exec->in = dup(0);
	while (temp)
	{
		exec->out = dup(1);
		if (temp->next)
		{
			if (pipe(exec->pipefd) == -1)
				handling_errors(exec, NULL, 3);
			exec->out = exec->pipefd[1];
		}
		redirections(temp, env, exec);
		create_children(temp, env, exec);
		exec->in = exec->pipefd[0];
		temp = temp->next;
	}
	waiting_proccesses(exec, cmd);
}
