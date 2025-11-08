#include "minishell.h"

int		check_sintax(char *str, t_map *env);

void	print_struct(t_cmd *head)
{
	t_cmd	*node;
	int		i;
	t_redir	*redir_node;

	node = head;
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
			redir_node = node->redir;
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

int	remove_redir(t_cmd *head, int i)
{
	int		len;
	char	**tmp;
	t_cmd	*node;

	len = arr_count(head->args);
	free(head->args[i]);
	free(head->args[i + 1]);
	ft_memmove(&head->args[i], &head->args[i + 2], (len - i - 1)
		* sizeof(char *));
	return (1);
}

int	is_empty(char *input)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (input[i])
	{
		if (input[i++] != ' ')
		{
			flag = true;
			break ;
		}
	}
	return (flag == true);
}

char	*primary_check(char *input, t_map *env)
{
	char	*dup;

	if (!input || !is_empty(input) || !check_sintax(input, env)
		|| !quote_handler(input))
		return (NULL);
	dup = ft_strdup(input);
	if (!dup)
		return (NULL);
	dup = unlink_redir(dup);
	if (!dup)
		return (NULL);
	return (dup);
}

t_cmd	*parsing(char *input, t_cmd *head, t_map *env)
{
	int		i;
	char	**line;

	input = primary_check(input, env);
	if (!input)
		return (NULL);
	line = ft_split(input, '\2');
	if (!line)
		return (perror("Allocation Error"), NULL);
	i = 0;
	while (line[i])
	{
		head = separate_args(head, line[i], env);
		if (!head)
			return (free_double(line), NULL);
		i++;
	}
	free(input);
	free_double(line);
	if (!init_redir(head))
		return (NULL);
	if (!change_expansion(head, env))
		return (NULL);
	remove_quotes(head);
	return (head);
}
