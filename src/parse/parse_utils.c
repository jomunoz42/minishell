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
	int quote;
	bool flag;

	i = 0;
	quote = 0;
	flag = false;
	while (input[i])
	{
		if (input[i++] == '"')
		{
			flag = !flag;
			quote++;
		}
		if (flag)
		{
			if (input[i] == '|')
				input[i] = 127;
			else if (input[i] == ' ')
				input[i] = 8;
		}
	}
	if (quote % 2)
		error_exit("Open Quotes");
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
