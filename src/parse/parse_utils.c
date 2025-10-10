#include "minishell.h"

void	free_double(char **arg)
{
	int i;

	i = 0;
	if (!arg || !*arg)
		return ;
    while (arg[i])
        free(arg[i++]);
    free(arg);
    return ;
}

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
		else if (!flag && input[i] == '<')
			input[i] = 7;
		else if (!flag && input[i] == '>')
			input[i] = 6;
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

int check_redir(char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return(1);
		i++;
	}
	return (0);
}

void revert_redir(char **str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 7)
				str[i][j] = '<';
			else if (str[i][j] == 6)
				str[i][j] = '>';
			j++;
		}
		i++;
	}
}

t_redir *find_redir(t_cmd *node)
{
	int i;
	t_redir *redir;

	i = 0;
	redir = NULL;
	while (node->args[i])
	{
		revert_redir(node->args);
		if (check_redir(node->args[i]))
		{
			redir = malloc(sizeof(t_redir));
			if (!redir)
				ft_exit(0);
			redir->args[]
		}
		i++;
	}
	return (redir);
}
