/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:28:02 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/04 19:16:08 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static char	*get_path(char **env)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			str = env[i];
	}
	if (!*env)
		str = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	return (str);
}

char	*get_absolute_path(char **env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*temp;
	char	*str;
	int		i;

	if (ft_strncmp(cmd, "", 1) == 0)
		return ("");
	if (access(cmd, X_OK) == 0)
		return (cmd);
	str = get_path(env);
	if (str == NULL)
		return (NULL);
	i = -1;
	dirs = ft_split(str, ':');
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (free_double(dirs), path);
		free(path);
	}
	return (free_double(dirs), NULL);
} */
