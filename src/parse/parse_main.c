

#include "minishell.h"

int	quote_handler(char *input, int start)
{
	int j;
	int i;
	
	j = start;
	while (input[++j] != '"');
	if (input[j] == '\0')
	{
		perror("1 quote");
		exit(0);
	}
	else
	{
		input[start] = 127;
		input[j] = 127;
	}
	i = start;
	while (input[i])
	{
		if (input[i] != ' ')
			break;
		input[i++] = 127;
	}
	i = ft_strlen(input) - 1;
	while (input[i])
	{
		if (input[i] != ' ')
			break;
		input[i--] = 127;
	}
	return (j);
}

void	parsing(char *input)
{
	int		i;
	char	**arg;

	i = 0;
	if (!input)
		return ;
	while (input[i])
	{
		if (input[i] == '"')
			i = quote_handler(input, i);
		if (input[i] == ' ')
			input[i] = 127;
		i++;
	}
	arg = ft_split(input, 127);
	if (!arg)
		return ;
	i = 0;
	while (arg[i])
		printf("%s\n", arg[i++]);
}
