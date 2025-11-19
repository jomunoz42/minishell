/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:42 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/19 23:19:59 by pbongiov         ###   ########.fr       */
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
			ft_exit(0, &exec, cmd);
		if (*input)
			add_history(input);
		cmd = parsing(input, NULL, env);
		if (cmd)
			execute_command(cmd, env, &exec);
		else
			env->put(env, ft_strdup("?"), ft_strdup("0"));
		free_list(cmd);
		cmd = NULL;
		free(input);
	}
}
