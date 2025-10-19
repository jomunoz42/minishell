/* 

#include "minishell.h"

static void print_export(char **vars, int length)
{
    bool    quote_flag;
    int     i;
    int     j;

    i = 0;
    if (!vars)
        return ;
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
        if (quote_flag)
            write(1, "\"", 1);
        write(1, "\n", 1);
        i++;
    }
}

static char  **sort_export(char **vars, int length)
{
    int     i;
    bool    swapped;
    char    *temp;

    swapped = 1;
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
    return (vars);
}

char    **build_export(t_built *built, char **env)
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
        if (many_equals(env[i]))
            built->export->put(built->export, vars[0], &env[i][len_after_equal(env[i])]);
        else
            built->export->put(built->export, vars[0], vars[1]);
        free_double(vars);
    }
    remove_extra_vars(built);
    vars = built->export->to_str(built->export);
    built->export_len = 0;
    while(vars[built->export_len])
        built->export_len++;
    return (vars);
}

static void    build_exported(t_built *built)
{
    const char    **vars;
    int     i;

    if(!built->exported)
    {
        built->exported = new_map();
        if(!built->exported)
            ft_exit(1);
    }
    i = 1;
    while (built->input[i])
    {
        vars = ft_split(built->input[i], '=');
        map->put(map, vars[0], vars[1]);
        if (many_equals(built->input[i]))
            built->exported->put(built->exported, vars[0], &built->input[i][len_after_equal(vars[1])]);
        else
            built->exported->put(built->exported, vars[0], vars[1]);
        free_double(vars);
        i++;
    }
    vars = built->exported->to_str(built->exported);
    built->exported_len = 0;
    while(vars[built->exported_len])
        built->exported_len++;
}

void    ft_export(t_cmd *cmd, t_map *env)
{
    char    **export;
    char    **exported;
    printf("export: ", )
    export = NULL;
    exported = NULL;
    if (!built->export)
        export = build_export(built, env);
    else
        export = built->export->to_str(built->export);
    export = sort_export(export, built->export_len);
    if (count_arguments(built->input) > 1)
        build_exported(built);
    else
    {
        print_export(export, built->export_len);
        if (built->exported)
        {
            exported = built->exported->to_str(built->exported);
            exported = sort_export(exported, built->exported_len);
            print_export(exported, built->exported_len);
        }
    }
    free_double(export);
    free_double(exported);
} */




// void	ft_putchar_fd(char c, int fd)
// {
// 	if (fd >= 0)
// 		write(fd, &c, 1);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	a;

// 	if (!s)
// 		return ;
// 	a = 0;
// 	while (s[a] != '\0')
// 	{
// 		ft_putchar_fd(s[a], fd);
// 		a++;
// 	}
// }






















/* #include "map.h"

static void swap_var(t_node *a, t_node *b)
{
    char *key;
    char *value;

    key = a->key;
    value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = key;
    b->value = value;
}

t_node *sort_nodes(t_map_extra *this)
{
    t_node  *a;
    t_node  *b;
    int     swapped;

    if (!this->sort)
        return (this->head);
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        a = this->head;
        while (a && a->next)
        {
            b = a->next;
            if (this->sort(a, b) > 0)
            {
                swap_var(a, b);
                swapped = 1;
            }
            a = a->next;
        }
    }
    return (this->head);
} */