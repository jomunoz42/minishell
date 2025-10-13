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

void put_in(char **new, t_cmd *head)
{
	t_cmd *node;
	t_cmd *current;

	if (!new || !*new || !head)
		ft_exit(1);
	node = new_node(new);
	if (!node)
		ft_exit(0);
	current = head;
	while (current->next)
		current = current->next;
	current->next = node;
}

t_cmd *new_head()
{
	t_cmd *head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->args = NULL;
	head->next = NULL;
	head->redir = NULL;
	return (head);
}