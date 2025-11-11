#include "minishell.h"

void	print_struct(t_cmd *head);

t_map *get_map_addr(t_map *src)
{
	static t_map *env;

	if (src)
		env = src;
	return (env);
}

void	free_list(t_cmd *all)
{
	t_cmd	*current;
	t_cmd	*next;
	t_redir	*next_redir;

	if (!all)
		return ;
	current = all;
	while (current)
	{
		next = current->next;
		free_double(current->args);
		while (current->redir)
		{
			next_redir = current->redir->next;
			free(current->redir->args[0]);
			free(current->redir->args[1]);
			free(current->redir);
			current->redir = next_redir;
		}
		free(current);
		current = next;
	}
}

int	main(int argc, char **argv, char **environ)
{
	static t_exec	exec;
	t_map			*env;
	t_cmd			*cmd;
	char			*input;

	env = new_map();
	copy_env(env, environ, &exec);
	get_map_addr(env);
	cmd = NULL;

	while (1)
	{	
		sig_handler();
		input = readline("minishell$ ");
		if (!input)
			ft_exit(0, &exec, cmd);
		if (*input)
			add_history(input);
		cmd = parsing(input, NULL, env);
		if (cmd)
		{
			// print_struct(cmd);
			if (!ft_strncmp(cmd->args[0], "exit", 4))
				break ;
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			execute_command(cmd, env, &exec);
		}
		free_list(cmd);
		free(input);
	}
	free_list(cmd);
	rl_clear_history();
	env->destroy(env);
	unlink("/tmp/mini_temp");
}

// jomunoz@c2r3s6:~/Common_Core_42/Milestone3/minishell$ export var="cat Makefile | cat | cat | cat | cat"
// jomunoz@c2r3s6:~/Common_Core_42/Milestone3/minishell$ $var

// cat: '|': No such file or directory
// cat: cat: No such file or directory
// cat: '|': No such file or directory
// cat: cat: No such file or directory
// cat: '|': No such file or directory
// cat: cat: No such file or directory
// cat: '|': No such file or directory
// cat: cat: No such file or directory

// minishell$ export var="cat Makefile | cat | cat | cat | cat"
// minishell$ $var

// /usr/bin/cat: ''$'\002': No such file or directory
// /usr/bin/cat: cat: No such file or directory
// /usr/bin/cat: ''$'\002': No such file or directory
// /usr/bin/cat: cat: No such file or directory
// /usr/bin/cat: ''$'\002': No such file or directory
// /usr/bin/cat: cat: No such file or directory
// /usr/bin/cat: ''$'\002': No such file or directory
// /usr/bin/cat: cat: No such file or directory


// dentro de variaveis funciona apenas o primeiro comando e nao funcionam redirecoes