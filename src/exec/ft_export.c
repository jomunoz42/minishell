

#include "minishell.h"

static void print_export(char **vars, int length)
{
    bool    quote_flag;
    int     i;
    int     j;

    i = -1;
    if (!vars)
        return ;
    while(++i < length)
    {
        j = 0;
        quote_flag = false;
        printf("declare -x ");
        while(vars[i][j])
        {
            printf("%c", vars[i][j]);
            if (vars[i][j] == '=' && vars[i][j + 1] && !quote_flag)
            {
                quote_flag = true;
                printf("\"");
            }
            j++;
        }
        if (quote_flag)
            printf("\"");
        printf("\n");
    }
}

int  sort_export(t_node *a, t_node *b)
{
    if (!a || !b)
        return (0);
    return (ft_strcmp(a->key, b->key));
}

void    ft_export(t_cmd *cmd, t_map *env)
{
    const char  **vars;
    int         i;

    i = 0;
    env->sort = sort_export;
    vars = env->to_str(env);
    print_export(vars, count_arguments(vars));
}

/* 
1-       so o nome

2-      variavel sem valor mas com igual so aspas vazias
*/