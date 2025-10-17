
#include "minishell.h"

void    ft_unset(t_cmd *cmd, t_map *env, t_exec *exec)
{
    int i;

    i = 1;
    if (cmd->args[i])
    {
        while(cmd->args[i])
        {
            env->remove(env, cmd->args[i]);
            if (i < exec->env_len)
                exec->env_len--;
            i++;
        }
    }
}
