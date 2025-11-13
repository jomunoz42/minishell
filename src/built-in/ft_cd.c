

#include "minishell.h"

int					handle_folder_errors(t_cmd *cmd, char *path);
char				*find_last_slash(char *current_pwd);
int                handle_cd_options(t_cmd *cmd, char *current_pwd);
int                goes_nowhere(char *current_pwd);

static int    goes_home(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    path = env->get(env, "HOME");
    if (!path || path[0] == '\0')
        return (free(current_pwd), write(2, "bash: cd: HOME not set\n", 24), 1);
    if (file_or_directory(path, cmd) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                handle_cd_errors(path, 4);
            else
                perror("bash: cd");
            free(current_pwd);
            return (1);
        }
        env->put(env, "OLDPWD", ft_strdup(current_pwd));
        env->put(env, "PWD", ft_strdup(path));
    }
    free(current_pwd);
    return (0);
}

static int    goes_up(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    path = find_last_slash(ft_strdup(current_pwd));
    if (file_or_directory(path, cmd) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                handle_cd_errors(path, 4);
            else
                perror("bash: cd");
            free(path);
            free(current_pwd);
            return (1);
        }
        env->put(env, "PWD", ft_strdup(path));
        env->put(env, "OLDPWD", ft_strdup(current_pwd));
    }
    free(current_pwd);
    return (free(path), 0);
}

static int    absolute_and_relative(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    if (cmd->args[1][0] == '/')
        path = ft_strdup(cmd->args[1]);
    else
    {
        path = ft_strjoin(env->get(env, "PWD"), "/");
        path = ft_strjoin_free(path, cmd->args[1]);
    }
    if (file_or_directory(path, cmd) == 0)
    {
        if (chdir(path) != 0)
        {
            handle_folder_errors(cmd, path);
            free(path);
            free(current_pwd);
            return (1);
        }
        env->put(env, "OLDPWD", ft_strdup(current_pwd));
        env->put(env, "PWD", ft_strdup(path));
    }
    free(current_pwd);
    return (free(path), 0);
}

int	ft_cd(t_cmd *cmd, t_map *env)
{
    char    *current_pwd;

    current_pwd = getcwd(NULL, 0);
    if (!current_pwd)
    {
        current_pwd = env->get(env, "PWD");
        if (!current_pwd || current_pwd[0] == '\0')
            return (handle_cd_errors(NULL, 0));
    }
    if (cmd->args[1] && cmd->args[2])
        return (free(current_pwd), handle_cd_errors(NULL, 1));
    else if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
        return (goes_home(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], "-", 2))
        return (absolute_and_relative(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], "-", 1))
        return (handle_cd_options(cmd, current_pwd));
    else if (!ft_strncmp(cmd->args[1], "..", 3))
        return (goes_up(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], ".", 2))
        return (goes_nowhere(current_pwd));
    else
        return (absolute_and_relative(cmd, env, current_pwd));
    return (0);
}


// bash: cd: No such file or directory
// minishell$ echo $?
// 1
// minishell$ cd -
// bash: cd: -: No such file or directory
// free(): invalid pointer
// Aborted (core dumped)


// SOLVED, TESTAR COM BUEDA FORCA