#include "minishell.h"

static char	*pos_redir(char *str, int i)
{
	char	*tmp;

	tmp = ft_realloc_str(str, ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	str = tmp;
	ft_memmove(str + i + 1, str + i, ft_strlen(str + i) + 1);
	str[i] = '\3';
	return (str);
}

static char	*pre_redir(char *str, int i)
{
	char	*tmp;

	tmp = ft_realloc_str(str, ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	str = tmp;
	ft_memmove(str + i, str + i - 1, ft_strlen(str + i - 1) + 1);
	str[i] = '\3';
	return (str);
}

char	*unlink_redir(char *str)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		flag = identify_quote(str[i], flag);
		if (!flag && (str[i] == '>' || str[i] == '<'))
		{
			if (i > 0 && str[i - 1] != '\3' && str[i - 1] != '\0')
				str = pre_redir(str, i);
			if (!str)
				return (NULL);
			while (str[i] == str[i + 1])
				i++;
			if (str[i + 1] != '\3' && str[i + 1] != '\0')
				str = pos_redir(str, i + 1);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

t_redir	*redir_start(t_cmd *head, int i)
{
	t_redir	*node;
	t_redir	*current;

	if (!head->redir)
	{
		head->redir = new_redir(head, i);
		if (!head->redir)
			return (NULL);
		node = head->redir;
	}
	else
	{
		node = new_redir(head, i);
		if (!node)
			return (NULL);
		current = head->redir;
		while (current->next)
			current = current->next;
		current->next = node;
	}
	if (!remove_redir(head, i))
		return (NULL);
	return (node);
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
