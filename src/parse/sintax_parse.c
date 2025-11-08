#include "minishell.h"

int	is_valid_redir(char *str, int i)
{
	char	c;

	if (str[i] == '>' || str[i] == '<')
	{
		c = str[i];
		if (str[i + 1] == c && str[i + 2] == c)
			return (0);
		else if (str[i + 1] == '<' || str[i + 1] == '>')
		{
			if (c != str[i + 1])
				return (0);
		}
	}
	return (1);
}

int	is_valid_pipe(char *str, int end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= end)
	{
		if (!is_valid_redir(str, i))
			return (0);
		if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '|')
			count++;
		if (str[i] == '|' && count == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_sintax(char *str, t_map *env)
{
	int i;
	char flag;

	i = -1;
	while (str[++i])
	{
		flag = identify_quote(str[i], flag);
		if (flag)
			continue ;
		if (str[i] == '|' && !is_valid_pipe(str, i))
		{
			write(2, "bash: syntax error near unexpected token\n", 42);
			env->put(env, "?", ft_strdup("2"));
			return (0);
		}
	}
	return (1);
}