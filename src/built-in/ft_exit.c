

#include "minishell.h"

void	free_list(t_cmd *all);

int	ft_exit(int status, t_exec *exec, t_cmd *cmd)
{
    t_map *env;

    env = get_map_addr(NULL);
	//  INSERT STUFF TO FREE
	if (!exec->is_child)
		write(1, "exit\n", 6);
	free_list(cmd);
	rl_clear_history();
	env->destroy(env);
	unlink("/tmp/mini_temp");
	exit(status);
}
