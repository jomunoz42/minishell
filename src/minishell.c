/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:15:00 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/04 15:54:57 by pbongiov         ###   ########.fr       */
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

void print_list(t_map *map)
{
   printf("Primeiro argumento: %s\n", map->get(map, "1"));
   printf("Segundo argumento: %s\n", map->get(map, "2")); 
   printf("Terceiro argumento: %s\n", map->get(map, "3")); 
   printf("Quarto argumento: %s\n", map->get(map, "4"));  
}

int main(int argc, char **argv)
{
    /* char *args[] = {"ls", "-la", NULL};
    t_cmd cmd = {
        .args=args,
        .redir=NULL,
        .next=NULL
    };
    print_command(&cmd);
    ft_pwd();*/
    t_map	*map;
    char *input;
    
	map = new_map();
	if (!map)
		return (0);
    while (1)
    {
        input = readline("<minishell>: ");
        if (!ft_strncmp(input, "exit", sizeof(input)))
            break;
        parsing(input, map);
        free(input);
    }
    print_list(map);
}

// ./minishell ls >> END -la < t | wc

