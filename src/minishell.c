/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:15:00 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/02 21:53:15 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_command(t_cmd *cmd)
{
    int i;
    
    i = 0;
    while(cmd->args[i])
    {
        printf("args[%d]: %s \n", i, cmd->args[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    char *args[] = {"ls", "-la", NULL};
    t_cmd cmd = {
        .args=args,
        .redir=NULL,
        .next=NULL
    };
    print_command(&cmd);
}
