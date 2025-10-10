

#include "minishell.h"

void    copy_env(t_map *map, char **env);
void    print_env(t_map *env);
int     sort_export(t_node *a, t_node *b);

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
    if (!ft_strncmp(cmd->args[0], "exit", 5))
        return ;
    if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd);
    if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd();
    if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env);
    if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env);
}

int main(int argc, char **argv, char **environ)
{
    char *args[] = {"export", "-la", NULL};
    t_cmd cmd = 
    {
        .args=args,
        .redir=NULL,
        .next=NULL
    };
    t_map *env;

    env = new_map();
    copy_env(env, environ);

    is_built_in(&cmd, env);

    env->destroy(env);

    // env->sort = sort_export;
    // env->put(env, COPY("B"), COPY("HELLO B"));
    // env->put(env, COPY("C"), COPY("HELLO C"));
    // env->put(env, COPY("A"), COPY("HELLO A"));
    // env->put(env, COPY("D"), COPY("HELLO D"));

    // while (1)
    // {
    //     input = readline("<minishell>: ");



    //     if (*input)
    //         add_history(input);
    //     //parsing(input);
    //     free(input);
    // }
}

