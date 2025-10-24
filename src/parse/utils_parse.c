#include "minishell.h"

int	quote_count(char *str)
{
	bool	single_flag;
	bool	double_flag;
	int		i;

	i = 0;
	single_flag = false;
	double_flag = false;
	while (str[i])
	{
		if (str[i] == '"' && !single_flag)
			double_flag = !double_flag;
		else if (str[i] == '\'' && !double_flag)
			single_flag = !single_flag;
		i++;
	}
	if (single_flag || double_flag)
		return (perror("Open Quotes"), 0);
	return (1);
}

int	quote_handler(char *input)
{
	int		i;
	bool	s_flag;
	bool	d_flag;

	i = 0;
	s_flag = false;
	d_flag = false;
	if (!quote_count(input))
		return (0);
	while (input[i])
	{
		if (input[i] == '"')
			s_flag = !s_flag;
		if (input[i] == '"')
			d_flag = !d_flag;
		i++;
		if (s_flag || d_flag)
		{
			if (input[i] == '|')
				input[i] = 127;
			else if (input[i] == ' ')
				input[i] = 8;
		}
	}
	return (1);
}

void	revert_quote(char **line)
{
	int	i;
	int	j;

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

int	count_redir(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == c)
			i++;
		else
			return (0);
	}
	return (i > 2);
}
