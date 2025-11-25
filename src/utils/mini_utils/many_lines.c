/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:45:07 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/25 18:52:44 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_dir(char *str, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;
	char	**dirs;

	i = -1;
	dirs = ft_split(str, ':');
	if (!dirs)
		return (NULL);
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin_free(temp, cmd);
		if (access(path, X_OK) == 0)
			return (free_double(dirs), path);
		free(path);
	}
	return (free_double(dirs), cmd);
}

int	wait_and_open(t_redir *redir_temp)
{
	int	s;

	wait(&s);
	redir_temp->fd = open("/tmp/mini_temp", O_RDONLY);
	unlink("/tmp/mini_temp");
	return (convert_status(s));
}
