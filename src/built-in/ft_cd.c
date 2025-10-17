

#include "minishell.h"

static int    goes_home(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    path = env->get(env, "HOME");
    if (!path || path[0] == '\0')
        return (write(2, "bash: cd: HOME not set\n", 24), 1);
    if (file_or_directory(path) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                return (handle_cd_errors(path, 4), 1);
            else
                return (perror("bash: cd"), 1);
        }
        env->put(env, "OLDPWD", current_pwd);
        env->put(env, "PWD", path);
        return (0);
    }
    else
        return (1);
}

static int    goes_last_dir(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    path = env->get(env, "OLDPWD");
    if (!path || path[0] == '\0')
        return (write(2, "bash: cd: OLDPWD not set\n", 24), 1);
    if (file_or_directory(path) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                return (handle_cd_errors(path, 4), 1);
            else
                return (perror("bash: cd"), 1);
        }
        printf("%s\n", path);
        env->put(env, "PWD", path);
        env->put(env, "OLDPWD", current_pwd);
        return (0);
    }
    else
        return (1);
}

static int    goes_up(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *copy_pwd;
    char *path;

    copy_pwd = ft_strdup(current_pwd);
    path = find_last_slash(copy_pwd);
    if (chdir(path) != 0)
    {
        if (errno == EACCES)
            return (handle_cd_errors(path, 4), 1);
        else
            return (perror("bash: cd"), 1);
    }
    env->put(env, "PWD", path);
    env->put(env, "OLDPWD", current_pwd);
    return (0);
}

static int    absolute_or_relative(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    if (cmd->args[1][0] == '/')
        path = cmd->args[1];
    else
    {
        path = env->get(env, "PWD");
        path = ft_strjoin(path, "/");
        path = ft_strjoin(path, cmd->args[1]);
    }
    if (file_or_directory(path) == 0)
    {
        if (chdir(path) != 0)
            return (handle_folder_errors(cmd, path), 1);
        env->put(env, "OLDPWD", current_pwd);
        env->put(env, "PWD", path);
        return (0);
    }
    return (1);   // check this
}

//       && SEE RETURN VALUES     &&      CHECK ALLOCS FAILURE
int	ft_cd(t_cmd *cmd, t_map *env)
{
    char    *path;
    char    *current_pwd;

    current_pwd = getcwd(NULL, 0);
    if (!current_pwd)
    {
        current_pwd = env->get(env, "PWD");
        if (!current_pwd || current_pwd[0] == '\0')
            return (handle_cd_errors(NULL, 0), 1);
    }
    if (cmd->args[1] && cmd->args[2])
        return (handle_cd_errors(NULL, 1), 1);
    else if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
        return (goes_home(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], "-", 2))
        return (goes_last_dir(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], "..", 3))
        return (goes_up(cmd, env, current_pwd));
    else if (!ft_strncmp(cmd->args[1], ".", 2))
        return (0);
    else
        return (absolute_or_relative(cmd, env, current_pwd));
    return (0);
}
