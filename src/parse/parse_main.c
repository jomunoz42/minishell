#include "minishell.h"

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

int	check_sintax(t_cmd *head)
{
	int		i;
	t_cmd	*node;

	node = head;
	while (node)
	{
		i = 0;
		while (node->args[i])
		{
			if (count_redir(node->args[i]))
			{
				printf("minishell: syntax error near unexpected token\n");
				return (0);
			}
			i++;
		}
		node = node->next;
	}
	return (1);
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

char	*primary_check(char *input)
{
	char	*dup;

	if (!input || !is_empty(input) || !quote_handler(input))
		return (NULL);
	dup = ft_strdup(input);
	if (!dup)
		return (NULL);
	dup = unlink_redir(dup);
	if (!dup)
		return (NULL);
	return (dup);
}

char *verify_var(char *str, t_map *env)
{
	int i;
	int j;
	char *var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			j = 0;
			while (str[i + j] && str[i + j] != ' ')
				j++;
			var = ft_substr(str, i + 1, j);
			free(str);
			if (!var)
				return(NULL);
			str = env->get(env, var);
			free(var);
			if (!str)
				str = ft_strdup("");
			break;
		}
		i++;
	}
	return (str);
}

void	change_expansion(t_cmd *head, t_map *env)
{
	int i;
	int j;
	bool flag;
	t_cmd *node;

	node = head;
	while(node)
	{
		i = 0;
		flag = false;
		while (node->args[i])
		{
			j = 0;
			while(node->args[i][j])
			{
				if (node->args[i][j] == '\'')
					flag = !flag;
				if (!flag && node->args[i][j] == '$')
					node->args[i] = verify_var(node->args[i], env);
				j++;
			}
			i++;
		}
		node = node->next;
	}
}

t_cmd	*parsing(char *input, t_cmd *head, t_map *env)
{
	int		i;
	char	**line;

	input = primary_check(input);
	if (!input)
		return (NULL);
	line = ft_split(input, '|');
	if (!line)
		return (perror("Allocation Error"), NULL);
	i = 0;
	while (line[i])
	{
		head = separate_args(head, line[i]);
		if (!head)
			return (free_double(line), NULL);
		i++;
	}
	free(input);
	free_double(line);
	if (!init_redir(head) || !check_sintax(head))
		return (NULL);
	change_expansion(head, env);
	return (head);
}
