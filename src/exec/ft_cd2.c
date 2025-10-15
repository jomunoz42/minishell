
#include "minishell.h"

static char  *root_edge_case(char *path, char *new_path, int index)
{
    if (index == 0)
    {
        if (path[0] == '/')
        {
            new_path = malloc(2);
            if (!new_path)
                ft_exit(1);
            new_path[0] = '/';
            new_path[1] = '\0';
            return (new_path);
        }
        else
            return (NULL);
    }
    else
        return (NULL);
}

static char  *find_last_slash(char *path)
{
    char *new_path;
    int i;

    i = 0;
    while(path[i])
        i++;
    while (i > 0 && path[i] != '/')
        i--;
    root_edge_case(path, new_path, i);
    if (new_path)
        return (new_path);
    new_path = malloc(sizeof(char) * (i + 1));
    if (!new_path)
        ft_exit(1);
    ft_strlcpy(new_path, path, i + 1);
    new_path[i] = '\0';
    return (new_path);
}

int    goes_home(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
    {
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
    return (0); // check this
}

int    goes_last_dir(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    if (!ft_strncmp(cmd->args[1], "-", 2))
    {
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
    return (0); // check this
}

int    goes_up(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    if (!ft_strncmp(cmd->args[1], "..", 3))
    {
        path = find_last_slash(current_pwd);
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
    if (!ft_strncmp(cmd->args[1], ".", 2))
        return (0);
    return (0);  // check this
}
