

#include "minishell.h"

void    ft_env(t_built *built, char **env)
{
    char    **vars;
    int     i;

    built->env = new_map();
    if(!built->env)
        ft_exit(1);
    i = -1;
    while (env[++i])
    {
        vars = ft_split(env[i], '=');
        if (!vars)
            ft_exit(1);
        if (strncmp("LS_COLORS", env[i], 9) == 0)
            built->env->put(built->env, vars[0], &env[i][10]);
        else if (vars[1] && vars[1][0] != '\0')
            built->env->put(built->env, vars[0], vars[1]);
        free_double(vars);
    }
    vars = built->env->to_str(built->env);
    i = 0;
    while(vars[i])
        printf("%s\n", vars[i++]);
}

/* 
    t_map *m;
    char **str;
    int i = 0;

    m = new_map();

    m->put(m, "batata", "abc");
    m->put(m, "batata1", "abc1");
    str = m->to_str(m);
    while (str[i])
        printf("%s\n", str[i++]);
 */
