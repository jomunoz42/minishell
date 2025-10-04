/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:25:08 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/04 16:13:05 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_map *map)
{
	int		i;
	char	*s;
	char	**arg;

	i = 0;
	arg = ft_split(input, '|');
	if (!arg)
		return ;
	while (arg[i])
	{
		s = ft_itoa(i + 1);
		fprintf(stderr, "%s\n", s);
		if (!s)
		{
			free_double(arg);
			return ;
		}
		map->put(map, s, arg[i++]);
		free(s);
	}
	fprintf(stderr, "%s\n", map->get(map, "/1"));
	free_double(arg);
}
