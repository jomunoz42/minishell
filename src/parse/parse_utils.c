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

void quote_count(char *str)
{
	int single;
	int doble;
	int i;

	i = 0;
	single = 0;
	doble = 0;
	while (str[i])
	{
		if (str[i] == '"')
			doble++;
		else if (str[i] == '\'')
			single++;
		i++;
	}
	if (single % 2 || doble % 2)
		error_exit("Open quotes");
}

void quote_handler(char *input)
{
	int i;
	bool flag;

	i = 0;
	flag = false;
	quote_count(input);
	while (input[i])
	{
		if (input[i++] == '"')
			flag = !flag;
		if (flag)
		{
			if (input[i] == '|')
				input[i] = 127;
			else if (input[i] == ' ')
				input[i] = 8;
		}
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
