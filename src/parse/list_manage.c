#include "minishell.h"

char				*get_absolute_path(t_map *env, char *cmd);

t_cmd	*new_node(char **args, t_map *env)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(1);
	node->args = args;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*separate_args(t_cmd *head, char *line, t_map *env)
{
	char	**args;
	t_cmd	*node;
	t_cmd	*current;

	args = ft_split(line, '\3');
	if (!args)
		return (perror("Allocation Error"), NULL);
	if (!head)
		head = new_node(args, env);
	else
	{
		node = new_node(args, env);
		if (!node)
			return (NULL);
		current = head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	if (!head)
		return (perror("Allocation Error"), NULL);
	return (head);
}

t_redir	*new_redir(t_cmd *head, int i)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->args[0] = ft_strdup(head->args[i]);
	if (!new->args[0])
		return (NULL);
	new->args[1] = ft_strdup(head->args[i + 1]);
	if (!new->args[1])
		return (free(new->args[0]), NULL);
	new->next = NULL;
	new->fd = 0;
	return (new);
}

int	init_redir(t_cmd *head)
{
	int		i;
	t_cmd	*node;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			if (node->args[i][0] == '>' || node->args[i][0] == '<')
			{
				if (!node->args[i + 1])
					return (1);
				if (!redir_start(node, i))
					return (0);
				continue ;
			}
			i++;
		}
		node = node->next;
	}
	return (1);
}
