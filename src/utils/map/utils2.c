/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:22:03 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/11 18:06:41 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*ft_strdup(const char *s);
void	__put(t_map_extra *this, char *key, char *value);
char	*__get(t_map_extra *this, char *key);
void	__remove(t_map_extra *this, char *key);
char	**to_str(t_map_extra *this);
void	__destroy(t_map_extra *this);

t_map	*new_map(void)
{
	t_map_extra	*new;

	new = malloc(sizeof(t_map_extra));
	if (!new)
		return (NULL);
	new->size = 0;
	new->head = NULL;
	new->tail = NULL;
	new->is_change = 1;
	new->str = NULL;
	new->put = __put;
	new->get = __get;
	new->remove = __remove;
	new->to_str = to_str;
	new->destroy = __destroy;
	return ((t_map *)new);
}

t_node	*create_node(t_map_extra *this, char *key, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	free_s(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	if ((!str1 && str2) || (str1 && !str2))
		return (1);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
