

#include "minishell.h"

char	*get_absolute_path(t_map *env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*temp;
	char	*str;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	str = env->get(env, "PATH");
	if (!str || str[0] == '\0')
		return (cmd);
	i = -1;
	dirs = ft_split(str, ':');
	while (dirs[++i])
	{
		temp = ft_strjoin_free(dirs[i], "/");
		path = ft_strjoin_free(temp, cmd);
		if (access(path, X_OK) == 0)
			return (free(cmd), path);
		free(path);
	}
	return (cmd);
}
