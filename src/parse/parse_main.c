

#include "minishell.h"

void	quote_handler(char *input)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
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

void	revert_quote(char **line)
{
	int	i;
	int	j;

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

void put_in(char **new, t_cmd *all)
{
	
}

void	parsing(char *input, t_cmd *all)
{
	int		i;
	char	**line;
	char	**args;

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
		int	j = 0;
		revert_quote(args);
		put_in(args, all);
		i++;
	}
	//revert_quote(line);
}
