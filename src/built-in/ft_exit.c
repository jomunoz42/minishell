

#include "minishell.h"

void	free_list(t_cmd *all);

int	is_valid_exit_arg(char *arg)
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
	if (!is_valid_exit_arg(cmd->args[1]))
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
	free_list(cmd);
	rl_clear_history();
	env->destroy(env);
	if (!exec->is_child)
		unlink("/tmp/mini_temp");
	exit(status);
}

// exit ta foda, mas testa-lo