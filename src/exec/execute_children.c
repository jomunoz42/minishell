
#include "minishell.h"

int			is_it_built_in(char *cmd);
int			exec_built_in(t_cmd *cmd, t_map *env, t_exec *exec);
int			is_parent_built_ins(t_cmd *temp, t_map *env, t_exec *exec);
void		handle_built_in(t_cmd *cmd, t_cmd *temp, t_map *env, t_exec *exec);

static void	waiting_proccesses(t_cmd *cmd, t_exec *exec, t_map *env)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		waitpid(temp->pid, &exec->status, 0);
		temp = temp->next;
	}
	exec->status = convert_status(exec->status);
	env->put(env, ft_strdup("?"), ft_itoa(exec->status));
}

static void	redirections2(t_redir *temp, t_exec *exec, t_cmd *cmd)
{
	if (ft_strncmp(temp->args[0], ">>", 3) == 0)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->out == -1)
			handling_errors(exec, temp->args[1], 2, cmd);
	}
	if (ft_strncmp(temp->args[0], ">", 2) == 0)
	{
		if (exec->out > 2)
			close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->out == -1)
			handling_errors(exec, temp->args[1], 2, cmd);
	}
}

void	redirections(t_redir *redir, t_exec *exec, t_cmd *cmd)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (ft_strncmp(temp->args[0], "<<", 3) == 0)
		{
			if (exec->in > 2)
				close(exec->in);
			exec->in = open("/tmp/mini_temp", O_RDONLY);
			if (exec->in == -1)
				handling_errors(exec, "/tmp/mini_temp", 1, cmd);
		}
		if (ft_strncmp(temp->args[0], "<", 2) == 0)
		{
			if (exec->in > 2)
				close(exec->in);
			exec->in = open(temp->args[1], O_RDONLY);
			if (exec->in == -1)
			{
				if (handling_errors(exec, temp->args[1], 1, cmd))
					return ;
			}
		}
		redirections2(temp, exec, cmd);
		temp = temp->next;
	}
}

static void	create_children(t_cmd *cmd, t_cmd *temp, t_map *env, t_exec *exec)
{
	temp->pid = fork();
	if (temp->pid == -1)
		handling_errors(exec, NULL, 4, cmd);
	if (!temp->pid)
	{
		exec->is_child = true;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		no_file_no_perm(cmd, exec);
		handle_built_in(cmd, temp, env, exec);
		dup2(exec->in, 0);
		if (exec->in > 2)
			close(exec->in);
		dup2(exec->out, 1);
		if (exec->out > 2)
			close(exec->out);
		if (exec->pipefd[0])
			close(exec->pipefd[0]);
		if (temp->args[0])
			execve(temp->args[0], temp->args, env->to_str(env));
		handle_execve_errors(cmd, temp, env, exec);
	}
	close_and_reset(exec);
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)
{
	t_cmd	*temp;

	temp = cmd;
	if (execute_heredocs(cmd, temp, exec))
		return ;
	if (is_parent_built_ins(temp, env, exec))
		return ;
	exec->in = dup(0);
	while (temp)
	{
		exec->out = dup(1);
		if (temp->next)
		{
			if (pipe(exec->pipefd) == -1)
				handling_errors(exec, NULL, 3, cmd);
			close(exec->out);
			exec->out = exec->pipefd[1];
		}
		redirections(temp->redir, exec, cmd);
		create_children(cmd, temp, env, exec);
		exec->in = exec->pipefd[0];
		temp = temp->next;
	}
	waiting_proccesses(cmd, exec, env);
}
