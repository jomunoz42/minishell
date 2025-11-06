#include "minishell.h"

char	*pseudo_quotes(char *splited);
int		check_size(char *str);

char	**new_args_expanded(char **splited, t_cmd *node, int start)
{
	int		j;
	int		i;
	char	**new_args;

	new_args = ft_calloc(arr_count(node->args) + arr_count(splited) + 1,
			sizeof(char *));
	if (!new_args)
		return (NULL);
	i = -1;
	while (node->args[++i])
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
	}
	new_args[i] = NULL;
	free_double(splited);
	return (new_args);
}

int	split_expansion_helper(t_cmd *node, int i)
{
	char	**tmp;
   // char	*tmp_str;

	tmp = ft_split(node->args[i], '\3');
	if (!tmp)
		return (0);
	if (arr_count(tmp) > 1)
	{
		free_double(node->args);
		node->args = new_args_expanded(tmp, node, i);
		if (!node->args)
			return (0);
	}
	else if (node->args[i][0] == '&')
	{	
        //tmp_str = node->args[i];
        node->args[i] = pseudo_quotes(node->args[i]);
        //free(tmp_str);
    }
	free_double(tmp);
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
