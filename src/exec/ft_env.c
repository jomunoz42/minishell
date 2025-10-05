

#include "minishell.h"

char    *ls_colors_case(char **vars)
{
    int     i;
    char    *new_var;
    char    *temp;

    i = 1;
    new_var = vars[i];
    while (vars[i])
        printf("Vars[i] :%s\n", vars[i++]);
    i = 1;
    while(vars[i++])
    {
        temp = ft_strjoin(new_var, vars[i]);
        //free(new_var);
        //free(temp);
    }
    return(new_var);
}

void    ft_env(char **env)
{
    t_built *built;
    int     i;
    char    **vars;
    char    *edge_case;

    edge_case = NULL;
    built = malloc(sizeof(t_built));
    if (!built)
        ft_exit(1);
    built->env = new_map();
    if(!built->env)
        ft_exit(1);
    while (env[i])
    {
        vars = ft_split(env[i], '=');
        if (!vars)
            ft_exit(1);
        if (strcmp("LS_COLORS", env[i]) == 0)
            built->env->put(built->env, vars[0], &env[i] + 10);
        if(vars[1] && vars[1][0] != '\0')
            built->env->put(built->env, vars[0], vars[1]);
        // if (edge_case)
        //     free(edge_case);
        free_double(vars);
        i++;
    }
    vars = built->env->to_str(built->env);
    i = 0;
    while(vars[i])
    {
        printf("%s\n", vars[i]);
        i++;
    }
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
