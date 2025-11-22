/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:24:48 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/21 21:22:44 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_key_exists(char *arg, t_map *env)
{
	t_node	*node;

	node = env->head;
	while (node)
	{
		if (!strncmp(node->key, arg, ft_strlen(arg) + 1))
			return (1);
		node = node->next;
	}
	return (0);
}

char	**sort_vars(char **vars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (vars[i] && vars[i + 1])
	{
		if (ft_strcmp(vars[i], vars[i + 1]) > 0)
		{
			tmp = vars[i];
			vars[i] = vars[i + 1];
			vars[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (vars);
}

int	handle_invalid_export(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '=')
	{
		write(2, "bash: export: `", 15);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	while (arg[++i] && arg[i] != '=')
	{
		if (ft_isdigit(arg[0]) || !ft_isalnum_modified(arg[i]))
		{
			write(2, "bash: export: `", 15);
			write(2, arg, ft_strlen(arg));
			write(2, "': not a valid identifier\n", 27);
			return (1);
		}
	}
	return (0);
}
