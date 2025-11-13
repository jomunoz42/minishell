

#include "minishell.h"

void	free_list(t_cmd *all);

int exit_parsing(t_cmd *cmd, t_exec *exec, int status)
{
	if (cmd->args[2])
	{
		if (!exec->is_child)
			write(1, "exit\n", 6);
		write(2, "bash: exit: ", 12);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	if (!is_only_number(cmd->args[1]))
	{
		if (!exec->is_child)
			write(1, "exit\n", 6);
		write(2, "bash: exit: ", 12);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 28);
		if (!exec->is_child)
			write(1, "exit\n", 6);
		exec->is_child = !exec->is_child;
		ft_exit(2, exec, cmd);
	}
	ft_exit(status, exec, cmd);
}

int	ft_exit(int status, t_exec *exec, t_cmd *cmd)
{
    t_map *env;

    env = get_map_addr(NULL);
	while (status > 256)
	{
		status = status - 256;
	}                             //    test i had to leave


	if (!exec->is_child)
		write(1, "exit\n", 6);
	free_list(cmd);
	rl_clear_history();
	env->destroy(env);
	if (!exec->is_child)
		unlink("/tmp/mini_temp");
	exit(status);
}
