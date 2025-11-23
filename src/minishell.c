/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:42 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/23 21:28:16 by jomunoz          ###   ########.fr       */
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
		cmd = parsing(input, NULL);
		if (cmd)
			execute_command(cmd, env, &exec);
		free_list(cmd);
		cmd = NULL;
		free(input);
	}
}


// 1- Da seg com 1 ou mais espacos

// jomunoz@c2r5s6:~/Common_Core_42/Milestone3/minishell$ ./minishell
// minishell$ aaaa | | bbbb
// Segmentation fault (core dumped)



// 2-
//  minishell$ a <> b
//  a: command not found
//  (criab b)



// 3-  Em vez de dar sintax error da so para dar return??? se der trabalho caga.

// minishell$ aaaa || bbbb
// bash: syntax error near unexpected token



// 4-  O Gustavo descobriu mais este

// normal_bash$ <<< a
// normal_bash$ 

// minishell$ <<< a
// bash: syntax error near unexpected token

// ------->  Mas a partir de 4 da sintax error

// normal_bash$ <<<< a
// // bash: syntax error near unexpected token

// minishell$ <<<< a
// bash: syntax error near unexpected token

// ------->  Ja agora, se for assim >>> o bash da sintax error, para nao corrigir.