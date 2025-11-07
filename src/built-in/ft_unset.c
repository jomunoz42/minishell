
#include "minishell.h"

int    ft_unset(t_cmd *cmd, t_map *env)
{
    int i;

    i = 1;
    if (cmd->args[i])
    {
        while(cmd->args[i])
        {
            env->remove(env, cmd->args[i]);
            i++;
        }
    }
    return (0);
}
