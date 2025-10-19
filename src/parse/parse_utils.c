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
		return (perror("Oprn Quotes"), 0);
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

static char	*pos_redir(char *str, int i)
{
	char *tmp;

	tmp = realloc(str, ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	str = tmp;
	ft_memmove(str + i + 1, str + i, ft_strlen(str + i) + 1);
	str[i] = ' ';
	return (str);
}

static char	*pre_redir(char *str, int i)
{
	str = ft_realloc(str, ft_strlen(str) + 2);
	if (!str)
		return (NULL);
	ft_memmove(str + i, str + i - 1, ft_strlen(str + i - 1) + 1);
	str[i] = ' ';
	return (str);
}

int count_redir(char *str)
{
	int i;

	i = 0;
	while (str[i] == '<' || str[i] == '>')
		i++;
	return (i > 2);
}

char *space_between(char *str)
{
	int i;
	int j;
	char *new;

	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		// if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
		// {
		// 	new[j + i] = ' ';
		// 	j++;
		// }
		if (str[i] == '>' || str[i] == '<')
		{
			char c = str[i];
			while (str[i + j] == c)
				j++;
			new[j + i] = ' ';
			j++;
		}
		new[i + j] = str[i];
		i++;
	}
	new[i + j] = '\0';
	fprintf(stderr, "%s", new);
	exit(0);
	free(str);
	return (new);
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
			str = space_between(str);
			// if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\0')
			// 	str = pre_redir(str, i);
			// if (!str)
			// 	return (NULL);
			// while (str[i] == str[i + 1])
			// 	i++;
			// if (str[i + 1] != ' ' && str[i + 1] != '\0')
			// 	str = pos_redir(str, i + 1);
			// if (!str)
			// 	return (NULL);
		}
		i++;
	}
	return (str);
}
