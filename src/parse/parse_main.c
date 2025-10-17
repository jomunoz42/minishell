#include "minishell.h"

void print_struct(t_cmd *head)
{
	t_cmd *node;
	int i;

	node = head;
	while (node)
	{
		i = 0;
		printf("==========================\n");
		while (node->args && node->args[i])
			printf("ARGS: %s\n", node->args[i++]);
		printf("==========================\n");
		if (node->redir)
		{
			printf("==========================\n");
			while (node->redir)
			{
				i = 0;
				while (node->redir->args[i])
				{
					printf("REDIR: %s\n", node->redir->args[i++]);
					printf("==========================\n");\
				}
				node->redir = node->redir->next;
			}
		}
		node = node->next;
	}
}

void	check_sintax(t_cmd *head)
{
	int i;
	t_cmd *node;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			if (count_redir(node->args[i]))
				error_exit("Sintax error", 22);
			i++;
		}
		node = node->next;
	}
}

t_redir *new_redir(t_cmd *head, int i)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return NULL;
	new->args[0] = ft_strdup(head->args[i]);
	new->args[1] = ft_strdup(head->args[i + 1]);
	new->next = NULL;
	new->fd = 0;
	return (new);
}

int arr_count(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void remove_redir(t_cmd *head, int i)
{
	int len;
	char **tmp;

	len = arr_count(head->args);
	free(head->args[i]);
	free(head->args[i + 1]);
	ft_memmove(&head->args[i], &head->args[i + 2], (len - i - 1) * sizeof(char *));
	tmp = realloc(head->args, (len - 2) * sizeof(char *));
	if (!tmp)
		ft_exit(1);
	head->args = tmp;
}

t_redir *redir_start(t_cmd *head, int i)
{
	t_redir *node;
	t_redir *current;

	if (!head->redir)
		head->redir = new_redir(head, i);
	else
	{
		node = new_redir(head, i);
		if (!node)
			ft_exit(0);
		current = head->redir;
		while(current->next)
			current = current->next;
		current->next = node;
	}
	remove_redir(head, i);
	return (head->redir);
}

void	init_redir(t_cmd *head)
{
	int i;
	t_cmd *node;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			if (node->args[i][0] == '>' || node->args[i][0] == '<')
			{
				if (!node->args[i + 1])
					return ;
				node->redir = redir_start(node, i);
			}
			i++;
		}
		node = node->next;
	}
}

t_cmd *parsing(char *input, t_cmd *head)
{
	int i;
	int j;
	char **line;
	char **args;

	if (!input)
		ft_exit(1);
	quote_handler(input);
	input = unlink_redir(input);
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
		head = put_in(args, head);
		free_double(args);
		i++;
	}
	init_redir(head);
	check_sintax(head);
	free_double(line);
	return (head);
}
