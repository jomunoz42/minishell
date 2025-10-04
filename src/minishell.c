/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:15:00 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/04 19:29:24 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    char *input;
    
    while (1)
    {
        input = readline("<minishell>: ");
        if (!ft_strncmp(input, "exit", sizeof(input)))
            break;
        if (*input)
            add_history(input);
        parsing(input);
        free(input);
    }
}

// ./minishell ls >> END -la < t | wc

