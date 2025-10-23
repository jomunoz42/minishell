
#include "minishell.h"

static int    is_built_in(t_cmd *cmd, t_map *env, t_exec *exec) // return values
{
    if (!cmd || !cmd->args)
        return (0);  // ?       
    if (!ft_strncmp(cmd->args[0], "cd", 3))
        ft_cd(cmd, env);
    if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd, env);
    if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd(env);
    if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env, exec);
    if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env, exec);
	return (0);
}

static void waiting_proccesses(t_cmd *cmd, t_exec *exec)
{
	t_cmd *temp;

	temp = cmd;
	while (temp)
	{
		if (!temp->next)
			waitpid(temp->pid, &exec->status, 0);
		else
			waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
}

static void redirections(t_redir *redir, t_map *env, t_exec *exec)
{
	if (!redir)
		return ;
	if (ft_strncmp(redir->args[0], "<<", 3) == 0)
	{
		exec->in = open("temp", O_RDONLY);
	}
	if (ft_strncmp(redir->args[0], "<", 2) == 0)
	{
		exec->in = open(redir->args[1], O_RDONLY);
		if (exec->in == -1)
			handling_errors(exec, redir->args[1], 1);
	}
	if (ft_strncmp(redir->args[0], ">>", 3) == 0)
	{
		exec->out = open(redir->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->out == -1)
			handling_errors(exec, redir->args[1], 2);
	}
	if (ft_strncmp(redir->args[0], ">", 2) == 0)
	{
		exec->out = open(redir->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->out == -1)
			handling_errors(exec, redir->args[1], 2);
	}
}

void	create_children(t_cmd *cmd, t_map *env, t_exec *exec)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		handling_errors(exec, NULL, 4);
	if (!cmd->pid)
	{
		dup2(exec->in, 0);
		close(exec->in);
		dup2(exec->out, 1);
		close(exec->out);
		if (exec->pipefd[0])
			close(exec->pipefd[0]);
		execve(cmd->args[0], cmd->args, env->to_str(env));
		// handle_path_not_found(cmd->args[0], cmd->args);
	}
	if (exec->in)
		close(exec->in);
	if (exec->out)
		close(exec->out);
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)  // env ??
{
	t_cmd *temp;

	temp = cmd;
	if (is_built_in(cmd, env, exec))
		return ;
	execute_heredocs(cmd, exec);
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
		redirections(temp->redir, env, exec);
		create_children(temp, env, exec);
		exec->in = exec->pipefd[0];
		temp = temp->next;
	}
	waiting_proccesses(cmd, exec);
}





// cat /dev/random | echo a