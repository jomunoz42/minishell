#include "minishell.h"


void print_struct(t_cmd *head)
{
    t_cmd *node = head;
    int i;

    while (node)
    {
        printf("======== COMANDO =========\n");
        i = 0;
        if (node->args)
        {
            while (node->args[i])
                printf("ARGS: %s\n", node->args[i++]);
        }
        if (node->redir)
        {
            t_redir *redir_node = node->redir;

            while (redir_node)
            {
                printf("----- REDIRECIONAMENTO ----\n");
                i = 0;
                if (*redir_node->args)
                {
                    while (i < 2)
                        printf("REDIR: %s\n", redir_node->args[i++]);
                }
                redir_node = redir_node->next;
            }
        }
        printf("==========================\n\n");
        node = node->next;
    }
}

int	check_sintax(t_cmd *head)
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
				return(printf("minishell: syntax error near unexpected token\n"), 0);
			i++;
		}
		node = node->next;
	}
	return (1);
}

t_redir *new_redir(t_cmd *head, int i)
{
	t_redir *new;

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

int arr_count(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int remove_redir(t_cmd *head, int i)
{
	int len;
	char **tmp;
	t_cmd *node;

	len = arr_count(head->args);
	free(head->args[i]);
	free(head->args[i + 1]);
	ft_memmove(&head->args[i], &head->args[i + 2], (len - i - 1) * sizeof(char *));
	return (1);
}

t_redir *redir_start(t_cmd *head, int i)
{
	t_redir *node;
	t_redir *current;

	if (!head->redir)
	{
		head->redir = new_redir(head, i);
		if (!head->redir)
			return (NULL);
		node = head->redir;
	}
	else
	{
		node = new_redir(head, i);
		if (!node)
			return (NULL);
		current = head->redir;
		while(current->next)
			current = current->next;
		current->next = node;
	}
	if (!remove_redir(head, i))
		return (NULL);
	return (node);
}

int	init_redir(t_cmd *head)
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
					return (1);
				if (!redir_start(node, i))
					return (0);
				continue;
			}
			i++;
		}
		node = node->next;
	}
	return (1);
}

int is_empty(char *input)
{
	int i;
	bool flag;

	i = 0;
	flag = false;
	while (input[i])
	{
		if (input[i++] != ' ')
		{
			flag = true;
			break;
		}
	}
	return (flag == true);
}

t_cmd *parsing(char *input, t_cmd *head)
{
	int i;
	int j;
	char *dup;
	char **line;
	char **args;

	if (!input || !is_empty(input) || !quote_handler(input))
		return (NULL);
	dup = ft_strdup(input);
	if (!dup)
		return (NULL);
	dup = unlink_redir(dup);
	if (!dup)
		return (NULL);
	line = ft_split(dup, '|');
	if (!line)
		return (perror("Allocation Error"), NULL);
	i = 0;
	while (line[i])
	{
		args = ft_split(line[i], ' ');
		if (!args)
			return (free_double(line), perror("Allocation Error"), NULL);
		j = 0;
		revert_quote(args);
		head = put_in(args, head);
		if (!head)
			return (free_double(line), perror("Allocation Error"), NULL);
		i++;
	}
	if (!init_redir(head) || !check_sintax(head))
		return(free_double(line), NULL);
	free_double(line);
	free(dup);
	return (head);
}
