#include "minishell.h"

void	print_struct(t_cmd *head);

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
	cmd = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (*input)
			add_history(input);
		cmd = parsing(input, NULL, env);
		if (cmd)
		{
			print_struct(cmd);
			if (!ft_strncmp(cmd->args[0], "exit", 4))
				break ;
			execute_command(cmd, env, &exec);
		}
		free_list(cmd);
	}
	free(input);
	free_list(cmd);
	rl_clear_history();
	env->destroy(env);
	unlink("/tmp/mini_temp");
}

//          minishell$ cat < 2.txt wc < 3.txt
//          Segmentation fault (core dumped)

//          com printfs nao acontece e fica correto

// declare -x a="a

// export a=c b=a c=t   &a&b&c

// export a nao tira o valor de a

// echo dentro de fork

//    unset e cd e exit nao funcionam de pipe