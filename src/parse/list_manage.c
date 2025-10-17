#include "minishell.h"

t_cmd *new_node(char **new)
{
	int i;
	t_cmd *node;

	if (!new || !*new)
		return (NULL);
	i = 0;
	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(1);
	while (new[i++]);
	node->args = malloc(sizeof(char *) * i);
	if (!node->args)
		return (free(node), NULL);
	i = -1;
	while (new[++i])
	{
		node->args[i] = ft_strdup(new[i]);
		if (!node->args[i])
			return (free(node), free_double(node->args), NULL);
	}
	node->args[i] = NULL;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_cmd *put_in(char **new, t_cmd *head)
{
	t_cmd *node;
	t_cmd *current;

	if (!new || !*new)
		ft_exit(1);
	if (!head)
		head = new_node(new);
	else
	{
		node = new_node(new);
		if (!node)
			ft_exit(0);
		current = head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	return (head);
}
