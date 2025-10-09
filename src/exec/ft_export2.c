
#include "minishell.h"

int len_after_equal(char *vars)
{
    int i;

    i = 0;
    if (!vars)
        return(0);
    while(vars[i] && vars[i] != '=')
        i++;
    i++;
    return (i);
}

int many_equals(char *vars)
{
    int count;
    int i;

    i = 0;
    count = 0;
    if (!vars)
        return(0);
    while(vars[i])
    {
        if (vars[i] == '=')
            count++;
        i++;
    }
    if (count > 1)
        return(1);
    else
        return (0);
}

void    remove_extra_vars(t_built *built)
{
    built->export->remove(built->export, "_");
    built->export->remove(built->export, "MAKEFLAGS");
    built->export->remove(built->export, "MAKELEVEL");
    built->export->remove(built->export, "MAKE_TERMERR");
    built->export->remove(built->export, "MAKE_TERMOUT");
    built->export->remove(built->export, "MFLAGS");
}

int count_arguments(char **input)
{
    int i;

    i = 1;
    if (!input[i])
        return(1);
    while(input[i])
        i++;
    return(i);
}
