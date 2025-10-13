#include "minishell.h"

void	quote_count(char *str)
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
		error_exit("Open quotes", 8);
}

void	quote_handler(char *input)
{
	int		i;
	bool	s_flag;
	bool	d_flag;

	i = 0;
	s_flag = false;
	d_flag = false;
	quote_count(input);
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

static char	*pos_redir(char *str, int i)
{
	str = ft_realloc(str, ft_strlen(str) + 2);
	if (!str)
		ft_exit(0);
	ft_memmove(str + i + 1, str + i, ft_strlen(str + i) + 1);
	str[i] = ' ';
	return (str);
}

static char	*pre_redir(char *str, int i)
{
	str = ft_realloc(str, ft_strlen(str) + 2);
	if (!str)
		ft_exit(0);
	ft_memmove(str + i, str + i - 1, ft_strlen(str + i - 1) + 1);
	str[i] = ' ';
	return (str);
}

char	*unlink_redir(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (str[i])
	{
		if (str[i] == '"')
			flag = !flag;
		if (!flag && (str[i] == '>' || str[i] == '<'))
		{
			if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\0')
				str = pre_redir(str, i);
			if (str[i] == str[i + 1])
				i++;
			if (str[i + 1] != ' ' && str[i + 1] != '\0')
				str = pos_redir(str, i + 1);
		}
		i++;
	}
	return (str);
}
