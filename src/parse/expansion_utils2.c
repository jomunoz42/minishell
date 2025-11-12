#include "minishell.h"

char	*pseudo_quotes(char *splited);
int		check_size(char *str);

char	**new_args_expanded(char **splited, t_cmd *node, int start)
{
	int		j;
	int		i;
	int		size;
	char	**new_args;

	size = arr_count(node->args) + arr_count(splited);
	new_args = ft_calloc(size + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		if (i == start)
		{
			j = -1;
			while (++j < arr_count(splited))
				new_args[i + j] = pseudo_quotes(splited[j]);
			i = i + j;
			continue ;
		}
		else
			new_args[i] = node->args[i];
		i++;
	}
	return (new_args);
}

int	split_expansion_helper(t_cmd *node, int i)
{
	char	*tmp_str;
	char	**splited;
	char	**tmp_double;

	splited = ft_split(node->args[i], '\3');
	if (!splited)
		return (0);
	if (arr_count(splited) > 1)
	{
		tmp_double = node->args;
		node->args = new_args_expanded(splited, node, i);
		if (!node->args)
			return (free_double(splited), 0);
		free_double(tmp_double);
	}
	else if (node->args[i][0] == '\2')
	{
		tmp_str = node->args[i];
		node->args[i] = pseudo_quotes(node->args[i]);
		free(tmp_str);
	}
	free_double(splited);
	return (1);
}

int	verify_var_sintax(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = check_size(str);
	if (!ft_isalnum_modified(str[i]) && str[i] != '?' && str[i] != '$')
		return (0);
	while (i < j && str[i])
	{
		if (!ft_isalnum_modified(str[i++]))
			return (0);
	}
	return (1);
}
