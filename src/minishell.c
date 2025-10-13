#include "minishell.h"

void print_struct(t_cmd *head);
// void    print_command(t_cmd *cmd)
// {
//     int i;
    
//     i = 0;
//     while(cmd->args[i])
//     {
//         printf("args[%d]: %s \n", i, cmd->args[i]);
//         i++;
//     }
// }

// void print_list(t_map *map)
// {
//    printf("Primeiro argumento: %s\n", map->get(map, "1"));
//    printf("Segundo argumento: %s\n", map->get(map, "2")); 
//    printf("Terceiro argumento: %s\n", map->get(map, "3")); 
//    printf("Quarto argumento: %s\n", map->get(map, "4"));  
// }

static void    is_built_in(t_cmd *cmd, t_map *env)
{
    if (!cmd || !cmd->args)
        return;
    if (!ft_strncmp(cmd->args[0], "exit", 5))
        ft_exit(0);
    else if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd);
    else if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    else if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env);
    else if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env);
}

void free_list(t_cmd *all)
{
    t_cmd *current;
    t_cmd *next;

    if (!all)
        return;
    current = all;
    while (current)
    {
        next = current->next;
        if (current->args)
            free_double(current->args);
        free(current);
        current = next;
    }
}

int main(int argc, char **argv, char **environ)
{
    char *input;
    t_cmd *cmd;
    t_map *env;

    env = new_map();
    copy_env(env, environ);
    while (1)
    {
        input = readline("<minishell>: ");
        if (*input)
        add_history(input);
        cmd = new_head();
        if (!cmd)
            break;
        parsing(input, cmd);
        //print_struct(cmd);
        is_built_in(cmd->next, env);
        free_list(cmd);
    }
    rl_clear_history();
    env->destroy(env);
}

