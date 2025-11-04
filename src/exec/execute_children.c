
#include "minishell.h"

int			is_built_in(t_cmd *cmd, t_map *env, t_exec *exec);
char		*get_absolute_path(t_map *env, char *cmd);

static void	waiting_proccesses(t_cmd *cmd, t_exec *exec, t_map *env)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (!temp->next)
			waitpid(temp->pid, &exec->status, 0);
		else
			waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
	if (WIFEXITED(exec->status))
		env->put(env, "?", ft_itoa(WEXITSTATUS(exec->status)));
}

static void	redirections2(t_redir *temp, t_exec *exec)
{
	if (ft_strncmp(temp->args[0], ">>", 3) == 0)
	{
		close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (exec->out == -1)
			handling_errors(exec, temp->args[1], 2);
	}
	if (ft_strncmp(temp->args[0], ">", 2) == 0)
	{
		close(exec->out);
		exec->out = open(temp->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (exec->out == -1)
			handling_errors(exec, temp->args[1], 2);
	}
}

static void	redirections(t_redir *redir, t_exec *exec)
{
	t_redir	*temp;

	temp = redir;
	while (temp)
	{
		if (ft_strncmp(temp->args[0], "<<", 3) == 0)
		{
			close(exec->in);
			exec->in = open("/tmp/mini_temp", O_RDONLY);
			if (exec->in == -1)
				handling_errors(exec, temp->args[1], 1);
					// errado e check this error id   1??
		}
		if (ft_strncmp(temp->args[0], "<", 2) == 0)
		{
			close(exec->in);
			exec->in = open(temp->args[1], O_RDONLY);
			if (exec->in == -1)
				handling_errors(exec, temp->args[1], 1);
		}
		redirections2(temp, exec);
		temp = temp->next;
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
		if (exec->no_file == true)
			exit(1);
		if (exec->no_permission == true)
			exit(126);
		execve(cmd->args[0], cmd->args, env->to_str(env));
		handle_path_not_found(cmd->args[0], cmd->args);
	}
	if (exec->in)
		close(exec->in);
	if (exec->out)
		close(exec->out);
	exec->no_file = false;
	exec->no_permission = false;
}

void	execute_command(t_cmd *cmd, t_map *env, t_exec *exec)
{
	t_cmd	*temp;

	temp = cmd;
	exec->in = -1;
	exec->out = -1;
	if (is_built_in(cmd, env, exec))
		return ;
	cmd->args[0] = get_absolute_path(env, cmd->args[0]);
	execute_heredocs(cmd, exec);
	exec->in = dup(0);
	while (temp)
	{
		exec->out = dup(1);
		if (temp->next)
		{
			if (pipe(exec->pipefd) == -1)
				handling_errors(exec, NULL, 3);
			close(exec->out);
			exec->out = exec->pipefd[1];
		}
		redirections(temp->redir, exec);
		create_children(temp, env, exec);
		exec->in = exec->pipefd[0];
		temp = temp->next;
	}
	waiting_proccesses(cmd, exec, env);
}

//    ./minishell ls >> END cat < fd | wc     SEG FAULT

//    cat < 2.txt < 1.txt | cat > 3.txt

// Temporary heredoc file handling:

// You overwrite exec->in and exec->out multiple times          SEEMS CORRECT -

// Close pipefd in parent processes properly:             SEEMS CORRECT -

// Exit codes of commands

// Variable expansion in heredocs: Bash may do expansions
// in heredoc content unless quotes are used around delimiters.

// cat /dev/random | echo a
