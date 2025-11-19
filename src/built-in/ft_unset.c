/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:02 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/19 19:29:26 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_map *env)
{
	int	i;

	i = 1;
	if (cmd->args[i])
	{
		while (cmd->args[i])
		{
			env->remove(env, cmd->args[i]);
			i++;
		}
	}
	return (0);
}
