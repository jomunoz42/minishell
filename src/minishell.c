/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:42 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/22 19:24:25 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_map_addr(t_map *src)
{
	static t_map	*env;

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
	copy_env(env, environ, &exec, NULL);
	((void)argc, (void)argv);
	while (1)
	{
		sig_handler();
		input = readline("minishell$ ");
		if (!input)
			ft_exit(0, &exec, NULL);
		if (*input)
			add_history(input);
		cmd = parsing(input, NULL, &exec);
		if (cmd)
			execute_command(cmd, env, &exec);
		else if (!exec.no_file)
			env->put(env, ft_strdup("?"), ft_strdup("0"));
		free_list(cmd);
		cmd = NULL;
		free(input);
	}
}

// 1-
// << $'USER' cat
// << $""''USER"" cat

// 2-
// CONTROL \ enquanto valgrind esta activo da core dumped e normal?
// fica tudo breakado

// 3-
// sleep 5000 ctrl c         should print the promt in a new line

// normal_bash$ sleep 5000
// ^C
// normal_bash$

// minishell$ sleep 5000
// ^Cminishell$ sleep 5000

// 4- enter sem nada nao muda para 0, matem o que ja estava
// normal_bash$ ^C           (status 130)
// normal_bash$
// normal_bash$ echo $?
// 130

// minishell$ ^C
// minishell$
// minishell$ echo $?
// 0
