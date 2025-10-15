#include "minishell.h"

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
		put_in(args, head);
		free_double(args);
		i++;
	}
	free_double(line);
}
