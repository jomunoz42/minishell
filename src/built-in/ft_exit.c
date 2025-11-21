/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:20 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/21 18:34:47 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_list(t_cmd *all);

static int	is_valid_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
	{
		i++;
		if (!arg[1] || !ft_isdigit(arg[1]))
			return (0);
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->args[1]);
	if (ft_isdigit(cmd->args[1][0]))
	{
		if (size > 19)
			return (1);
		if (size == 19 && (cmd->args[1][18] == '8' || cmd->args[1][18] == '9'))
			return (1);
	}
	if (cmd->args[1][0] == '+' || cmd->args[1][0] == '-')
	{
		if (size > 20)
			return (1);
		if (size == 20 && cmd->args[1][19] == '9')
			return (1);
	}
	return (0);
}

int	exit_parsing(t_cmd *cmd, t_exec *exec)
{
	int	status;

	if (cmd->args[2] && is_valid_exit_arg(cmd->args[1]))
	{
		if (!exec->is_child)
			write(1, "exit\n", 6);
		write(2, "bash: exit: too many arguments\n", 31);
		exec->msg_printed = true;
		return (1);
	}
	else if (!is_valid_exit_arg(cmd->args[1]) || check_overflow(cmd))
	{
		if (!exec->is_child)
			write(1, "exit\n", 6);
		write(2, "bash: exit: ", 12);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 28);
		exec->msg_printed = true;
		ft_exit(2, exec, cmd);
	}
	status = ft_atoi(cmd->args[1]);
	ft_exit(status, exec, cmd);
	return (0);
}

int	ft_exit(int status, t_exec *exec, t_cmd *cmd)
{
	t_map	*env;

	env = get_map_addr(NULL);
	while (status > 256)
		status -= 256;
	while (status < 0)
		status += 256;
	if (!exec->is_child && !exec->msg_printed)
		write(1, "exit\n", 6);
	if (cmd)
		free_list(cmd);
	rl_clear_history();
	if (env)
		env->destroy(env);
	if (!exec->is_child)
		unlink("/tmp/mini_temp");
	close_everything(exec);
	exit(status);
}
