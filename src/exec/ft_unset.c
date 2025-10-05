
#include "minishell.h"

void    ft_unset(char **env)
{
    t_map *m;
    char **str;
    int i = 0;

    m = new_map();

    m->put(m, "batata", "abc");
    m->put(m, "batata1", "abc1");
    str = m->to_str(m);
    while (str[i])
        printf("%s\n", str[i++]);
}
