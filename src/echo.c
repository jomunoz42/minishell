/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:30:02 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/02 21:39:41 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int i;
	int j;
	int n_exists;

	i = 0;
	j = 0;
	n_exists = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((ft_strncmp(&args[i][j], "-n", 3) == 0)
				|| (ft_strncmp(&args[i][j], "-nn", 3) == 0))
			{
                n_exists = 1;
				i++;
				break ;
			}
			else
			{
				while(args[i][j])
				{
            		write(1, &args[i][j], 1);
            		j++;
				}
				write(1, " ", 1);
				i++;
			}
		}
	}
    if (n_exists)
        write(1, "\n", 1);
    return (0);
}
