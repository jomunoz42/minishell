

#include "minishell.h"

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

int main(int argc, char **argv, char **env)
{
    /* char *args[] = {"ls", "-la", NULL};
    t_cmd cmd = {
        .args=args,
        .redir=NULL,
        .next=NULL
    };
    print_command(&cmd);
    ft_pwd();*/
    t_cmd *all;
    char *input;
    
    while (1)
    {
        input = readline("<minishell>: ");
        if (!ft_strncmp(input, "exit", sizeof(input)))
            break;
        if (*input)
            add_history(input);
        all = new_head();
        if (!all)
            break;
        parsing(input, all);
        //free(input);
        free_list(all);
    }
    rl_clear_history();
    //free(input);
}

// ./minishell ls >> END -la < t | wc

