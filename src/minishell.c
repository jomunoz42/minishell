/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:42 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/20 23:40:44 by jomunoz          ###   ########.fr       */
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

	cmd = NULL;
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

//                 I am on test 56




// minishell$ echo $SHLVL "$SHLVL" '$SHLVL' "$SH''LVL"


// ==43344== Invalid read of size 1
// ==43344==    at 0x407BD5: ft_memmove (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405777: expand_str (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x4058A1: expanded_arg (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405037: change_expansion (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405F55: parsing (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x409494: main (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==  Address 0x4b6aee6 is 3 bytes after a block of size 3 alloc'd
// ==43344==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==43344==    by 0x4090C7: ft_realloc_str (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405720: expand_str (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x4058A1: expanded_arg (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405037: change_expansion (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x405F55: parsing (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344==    by 0x409494: main (in /home/jomunoz/Common_Core_42/Milestone3/minishell/minishell)
// ==43344== 
// minishell$                  CONTROL D
// exit
// ==52903== 
// ==52903== FILE DESCRIPTORS: 3 open (3 std) at exit.
// ==52903== 
// ==52903== HEAP SUMMARY:
// ==52903==     in use at exit: 208,178 bytes in 222 blocks
// ==52903==   total heap usage: 668 allocs, 446 frees, 234,484 bytes allocated
// ==52903== 
// ==52903== LEAK SUMMARY:
// ==52903==    definitely lost: 0 bytes in 0 blocks
// ==52903==    indirectly lost: 0 bytes in 0 blocks
// ==52903==      possibly lost: 0 bytes in 0 blocks
// ==52903==    still reachable: 0 bytes in 0 blocks
// ==52903==         suppressed: 208,178 bytes in 222 blocks
// ==52903== 
// ==52903== For lists of detected and suppressed errors, rerun with: -s
// ==52903== ERROR SUMMARY: 3 errors from 1 contexts (suppressed: 0 from 0)


// bash: syntax error near unexpected token
// 3 "3 $SHLVL ''LVL

// correct =   3 3 $SHLVL ''LVL



//    ls"-l"|wc|grep|echo>>txt.txt<<EOF'A'"|">OUT      
//    deu erro e depois deixou de dar, confirmar mais uma vez



/* 
				bash :

	jomunoz@c2r2s8:~$ echo HI >    > out
	bash: syntax error near unexpected token `>'

				minishell:
	minishell$ echo HI >    > out
	minishell$ 
 */