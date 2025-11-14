
#include "minishell.h"

int	ft_isdigit_modified(int c);

int	length_of_equal(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i] && vars[i] != '=')
		i++;
	return (i);
}

int	is_there_equal(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i])
	{
		if (vars[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_there_value(char *vars)
{
	int	i;

	i = 0;
	if (!vars)
		return (0);
	while (vars[i])
	{
		if (vars[i] == '=')
		{
			if (vars[i + 1] != '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	is_there_slash(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	while (path[i])
	{
		if (path[i++] == '/')
			return (1);
	}
	return (0);
}
