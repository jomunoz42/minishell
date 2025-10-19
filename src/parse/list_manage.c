#include "minishell.h"

t_cmd *new_node(char **args, t_map *env)
{
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(1);
	node->args = args;
	node->args[0] = get_absolute_path(env, node->args[0]);
	node->redir = NULL;
	
	node->next = NULL;
	return (node);
}

t_cmd *put_in(char **new, t_cmd *head, t_map *env)
{
	t_cmd *node;
	t_cmd *current;

	if (!head)
		head = new_node(new, env);
	else
	{
		node = new_node(new, env);
		if (!node)
			return (NULL);
		current = head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	return (head);
}
