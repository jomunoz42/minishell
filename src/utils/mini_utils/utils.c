
#include "minishell.h"

char	*ft_strrchr(const char *s, int c);

void	free_double(char **arg)
{
	int i;

	i = 0;
	if (!arg)
		return ;
    while (arg[i])
        free(arg[i++]);
    free(arg);
    return ;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *result;
	
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char  *find_last_slash(char *current_pwd)
{
    char *last_slash;

    last_slash = strrchr(current_pwd, '/');
    if (last_slash)
    {
        if (last_slash == current_pwd)
            *(last_slash + 1) = '\0';
        else
            *last_slash = '\0';
    }
    return (current_pwd);
}

int    is_it_built_in(char *cmd)
{
    if (!cmd)
        return (0);     
    if (!ft_strncmp(cmd, "cd", 3))
        return (1);
    if (!ft_strncmp(cmd, "echo", 5))
        return (1);
    if (!ft_strncmp(cmd, "pwd", 4))
        return (1);
    if (!ft_strncmp(cmd, "env", 4))
        return (1);
    if (!ft_strncmp(cmd, "export", 7))
        return (1);
    if (!ft_strncmp(cmd, "unset", 6))
        return (1);
	return (0);
}

int     exec_cd_unset_exit(t_cmd *cmd, t_map *env, t_exec *exec)
{
    if (!cmd || !cmd->args)
        return (0);     
    if (!ft_strncmp(cmd->args[0], "cd", 3))
        return (ft_cd(cmd, env));
    if (!ft_strncmp(cmd->args[0], "unset", 6))
       return (ft_unset(cmd, env));
	return (0);
}