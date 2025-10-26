

#include "minishell.h"

void    copy_env(t_map *map, char **env, t_exec *exec)
{
    static char *args[2];
    int         j;
    int         i;

    i = -1;
    while (env[++i])
    {
        j = length_of_equal(env[i]);
        args[0] = ft_substr(env[i], 0, j++);
        args[1] = ft_substr(env[i], j, (ft_strlen(env[i]) - j));
        map->put(map, args[0], args[1]);
    }
}

void    ft_env(t_map *env)
{
    char    **vars;
    int     i;

    i = 0;
    vars = env->to_str(env);
    while(vars && vars[i] && is_there_value(vars[i]))
        printf("%s\n", vars[i++]);
}


//        IS  ENV -I ./MINISHELL    PROTECTED???????