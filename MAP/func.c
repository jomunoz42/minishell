/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:55:11 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/09 22:26:20 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		ft_strcmp(const char *str1, const char *str2);
char	**to_str_util(char **str, t_node *node);
t_node	*create_node(t_map_extra *this, char *key, char *value);

void	__put(t_map_extra *this, char *key, char *value)
{
	t_node	*node;

	if (!key)
		return ;
	node = this->head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			node->value = value;
			return ;
		}
		node = node->next;
	}
	node = create_node(this, key, value);
	if (!node)
		return ;
	if (!this->head)
		this->head = node;
	else
		this->tail->next = node;
	this->size++;
	this->tail = node;
}

char	*__get(t_map_extra *this, char *key)
{
	t_node	*current;

	current = this->head;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	__remove(t_map_extra *this, char *key)
{
	t_node	*node;
	t_node	*prev;

	prev = NULL;
	node = this->head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				this->head = node->next;
			if (node->key)
				free(node->key);
            if (node->value)
				free(node->value);
			free(node);
			this->size--;
			return ;
		}
		prev = node;
		node = node->next;
	}
}

char	**to_str(t_map_extra *this)
{
	char	**str;

	str = malloc(sizeof(char *) * (this->size + 1));
	if (!str)
		return (NULL);
	str = to_str_util(str, this->head);
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	return (str);
}

void	__destroy(t_map_extra *this)
{
	t_node	*next;
	t_node	*node;

	if (!this)
		return ;
	node = this->head;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	free(this);
	return ;
}
