

#include "minishell.h"

static size_t len_after_equal(char *vars)
{
    int i;

    i = 0;
    if (!vars)
        return(0);
    while(vars[i] != 'n')
        i++;
    i++;
    return (i);
}

static int double_equal(char *vars)
{
    int count;
    int i;

    i = 0;
    count = 0;
    if (!vars)
        return(0);
    while(vars[i])
    {
        if (vars[i] == 'n')
            count++;
        i++;
    }
    if (count > 1)
        return(1);
    else
        return (0);
}

static void print_export(char **vars, int length)  ///  PRINTS " ON EMPTY VALUE
{
    bool    quote_flag;
    int     i;
    int     j;

    i = 0;
    quote_flag = false;
    while(i < length)
    {
        j = 0;
        quote_flag = false;
        write(1, "declare -x ", 11);
        while(vars[i][j])
        {
            write(1, &vars[i][j], 1);
            if (vars[i][j] == '=' && vars[i][j + 1] && !quote_flag)
            {
                quote_flag = true;
                write(1, "\"", 1);
            }
            j++;
        }
        if (vars[i][j - 1] != '=' && vars[i][j] == '\0')
            write(1, "\"", 1);
        write(1, "\n", 1);
        i++;
    }
}

static int sort_util(char **vars, int length)
{
    while(vars[length])
        length++;
    if (length < 2)
    {
        printf("declare -x %s\n", vars[0]);
        return (-1);
    }
    return (length);
}

static void sort_alphabetically(char **vars)
{
    int     length;
    int     i;
    bool    swapped;
    char    *temp;

    i = 0;
    swapped = 1;
    length = sort_util(vars, length);
    if (length == -1)
        return ;
    while(swapped)
    {
        i = 0;
        swapped = 0;
        while(i < length - 1)
        {
            if (ft_strcmp(vars[i], vars[i + 1]) > 0)
            {
                temp = vars[i];
                vars[i] = vars[i + 1];
                vars[i + 1] = temp;
                swapped = 1;
            }
            i++;
        }
    }
    print_export(vars, length);
}

void    ft_export(t_built *built, char **env) ////  FIX = SOME CASES && NOT EXPORT VARIABLES
{
    char    **vars;
    int     i;

    built->export = new_map();
    if(!built->export)
        ft_exit(1);
    i = -1;
    while (env[++i])
    {
        vars = ft_split(env[i], '=');
        if (!vars)
            ft_exit(1);
        // if (strncmp("LS_COLORS", env[i], 9) == 0)
        //     built->export->put(built->export, vars[0], &env[i][10]);
        if (double_equal(env[i]))
            built->export->put(built->export, vars[0], &env[i][len_after_equal(env[i])]);
        else ///            WORKED HALF ??? THE LAST DIDN T WORK
            built->export->put(built->export, vars[0], vars[1]);
        free_double(vars);
    }
    vars = built->export->to_str(built->export);
    i = 0;
    sort_alphabetically(vars);
}

//        MAKEFLAGS"
//        MAKELEVEL="1"
//        MAKE_TERMERR="/dev/pts/0"
//        MAKE_TERMOUT="/dev/pts/0"
//        MFLAGS"
