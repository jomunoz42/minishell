/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:09:50 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/18 17:10:10 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_of_equal(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i] && vars[i] != '=')
		i++;
	return (i);
}

int	is_there_equal(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i])
	{
		if (vars[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_there_value(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i])
	{
		if (vars[i] == '=')
		{
			if (vars[i + 1] != '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	is_there_slash(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	while (path[i])
	{
		if (path[i++] == '/')
			return (1);
	}
	return (0);
}
