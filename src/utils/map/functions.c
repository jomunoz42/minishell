/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:55:11 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/12 22:28:48 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		ft_strcmp(const char *str1, const char *str2);
char	**to_str_util(t_map *this, char **str, t_node *node);
t_node	*create_node(t_map_extra *this, char *key, char *value);
void	free_s(char **str);

void	__put(t_map_extra *this, char *key, char *value)
{
	t_node	*node;

	if (!key)
		return ;
	node = this->head;
	this->is_change = 1;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			// free(key); // see this
			node->value = value;
			return ;
		}
		node = node->next;
	}
	node = create_node(this, key, value);
	if (++this->size && !node)
		return ;
	if (!this->head)
		this->head = node;
	else
		this->tail->next = node;
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
			this->is_change = 1;
			if (prev)
				prev->next = node->next;
			else
				this->head = node->next;
			if (node == this->tail)
                this->tail = prev;
			free(node->key);
			free(node->value);
			free(node);
			this->size--;
			if (this->size == 0)
                this->tail = NULL;
			return ;
		}
		prev = node;
		node = node->next;
	}
}

char	**to_str(t_map_extra *this)
{
	if (this->is_change == 0)
		return ((char **)this->str);
	this->is_change = 0;
	free_s(this->str);
	this->str = malloc(sizeof(char *) * (this->size + 1));
	if (!this->str)
		return (NULL);
	this->str = to_str_util((void *)this, this->str, this->head);
	return ((char **)this->str);
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
		free(node->key);
		free(node->value);
		free(node);
		node = next;
	}
	free_s(this->str);
	free(this);
	return ;
}
