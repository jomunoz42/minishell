

#include "minishell.h"

void quote_handler(char *input)
{
	int i;
	bool flag;

	i = 0;
	flag = false;
	while (input[i])
	{
		if (input[i] == '"')
			flag = !flag;
		if (flag)
		{
			if (input[i] == '|')
				input[i] = 127;
			else if (input[i] == ' ')
				input[i] = 8;
		}
		if (input[i] == '"')
			input[i] = ' ';
		i++;
	}
}

void revert_quote(char **line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == 127)
				line[i][j] = '|';
			else if (line[i][j] == 8)
				line[i][j] = ' ';
			j++;
		}
		i++;
	}
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
t_cmd *new_node(char **new)
{
	int i;
	t_cmd *node;

	if (!new || !*new)
		ft_exit(1);
	i = 0;
	node = malloc(sizeof(t_cmd));
	if (!node)
		ft_exit(1);
	while (new[i])
		i++;
	node->args = malloc(sizeof(char *) * (i + 1));
	if (!node->args)
		ft_exit(1);
	i = -1;
	while (new[++i])
	{
		node->args[i] = ft_strdup(new[i]);
		if (!node->args)
			ft_exit(1);
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
	current = head;
	while (current->next)
		current = current->next;
	current->next = node;
}

void print_struct(t_cmd *head)
{
	t_cmd *node;
	int i;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args && node->args[i])
			printf("ARGS: %s\n", node->args[i++]);
		printf("==========================\n");
		node = node->next;
	}
}

void parsing(char *input, t_cmd *head)
{
	int i;
	char **line;
	char **args;
	int j;

	if (!input)
		ft_exit(1);
	quote_handler(input);
	line = ft_split(input, '|');
	if (!line)
		ft_exit(1);
	i = 0;
	while (line[i])
	{
		args = ft_split(line[i], ' ');
		if (!args)
			ft_exit(1);
		j = 0;
		revert_quote(args);
		put_in(args, head);
		free_double(args);
		i++;
	}
	free_double(line);
	//print_struct(head);
}
