#include "minishell.h"

t_cmd *new_node(char **args)
{
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(1);
	node->args = args;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_cmd *put_in(char **new, t_cmd *head)
{
	t_cmd *node;
	t_cmd *current;

	if (!head)
		head = new_node(new);
	else
	{
		node = new_node(new);
		if (!node)
			return (NULL);
		current = head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	return (head);
}
