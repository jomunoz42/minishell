

#include "minishell.h"

int					handle_folder_errors(t_cmd *cmd, char *path, t_map *env);
char				*find_last_slash(char *current_pwd);
void                handle_cd_options(t_cmd *cmd, t_map *env, char *current_pwd);
void                goes_nowhere(t_map *env, char *current_pwd);

static void    goes_home(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    path = env->get(env, "HOME");
    if (!path || path[0] == '\0')
        (write(2, "bash: cd: HOME not set\n", 24), env->put(env, "?", ft_strdup("1")));
    if (file_or_directory(path, env) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                handle_cd_errors(path, 4, env);
            else
                (perror("bash: cd"), env->put(env, "?", ft_strdup("1")));
            free(path);
            free(current_pwd);
            return ;
        }
        env->put(env, "OLDPWD", current_pwd);
        env->put(env, "PWD", ft_strdup(path));
        env->put(env, "?", ft_strdup("0"));
    }
    else
        env->put(env, "?", ft_strdup("1"));
    free(path);
}

static void    goes_last_dir(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;
    
    path = env->get(env, "OLDPWD");
    if (!path || path[0] == '\0')
        (write(2, "bash: cd: OLDPWD not set\n", 24), env->put(env, "?", ft_strdup("1")));
    if (file_or_directory(path, env) == 0)
    {
        if (chdir(path) != 0)
        {
            if (errno == EACCES)
                handle_cd_errors(path, 4, env);
            else
                (perror("bash: cd"), env->put(env, "?", ft_strdup("1")));
            free(path);
            free(current_pwd);
            return ;
        }
        printf("%s\n", path);
        env->put(env, "PWD", ft_strdup(path));
        env->put(env, "OLDPWD", current_pwd);
        env->put(env, "?", ft_strdup("0"));
    }
    else
        env->put(env, "?", ft_strdup("1"));
    free(path);
}

static void    goes_up(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    path = find_last_slash(ft_strdup(current_pwd));
    if (chdir(path) != 0)
    {
        if (errno == EACCES)
            handle_cd_errors(path, 4, env);
        else
            (perror("bash: cd"), env->put(env, "?", ft_strdup("1")));
        free(path);
        free(current_pwd);
        return ;
    }
    env->put(env, "PWD", ft_strdup(path));
    env->put(env, "OLDPWD", current_pwd);
    env->put(env, "?", ft_strdup("0"));
    free(path);
}

static void    absolute_and_relative(t_cmd *cmd, t_map *env, char *current_pwd)
{
    char *path;

    if (cmd->args[1][0] == '/')
        path = ft_strdup(cmd->args[1]);
    else
    {
        path = ft_strjoin(env->get(env, "PWD"), "/");
        path = ft_strjoin_free(path, cmd->args[1]);
    }
    if (file_or_directory(path, env) == 0)
    {
        if (chdir(path) != 0)
        {
            handle_folder_errors(cmd, path, env);
            free(path);
            free(current_pwd);
            return ;
        }
        env->put(env, "OLDPWD", current_pwd);
        env->put(env, "PWD", ft_strdup(path));
        env->put(env, "?", ft_strdup("0"));
    }
    free(path);
}

void	ft_cd(t_cmd *cmd, t_map *env)
{
    char    *current_pwd;

    current_pwd = getcwd(NULL, 0);
    if (!current_pwd)
    {
        current_pwd = env->get(env, "PWD");
        if (!current_pwd || current_pwd[0] == '\0')
            handle_cd_errors(NULL, 0, env);
    }
    if (cmd->args[1] && cmd->args[2])
        handle_cd_errors(NULL, 1, env);
    else if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
        goes_home(cmd, env, current_pwd);
    else if (!ft_strncmp(cmd->args[1], "-", 2))
        goes_last_dir(cmd, env, current_pwd);
    else if (!ft_strncmp(cmd->args[1], "-", 1))
        handle_cd_options(cmd, env, current_pwd);
    else if (!ft_strncmp(cmd->args[1], "..", 3))
        goes_up(cmd, env, current_pwd);
    else if (!ft_strncmp(cmd->args[1], ".", 2))
        goes_nowhere(env, current_pwd);
    else
        absolute_and_relative(cmd, env, current_pwd);
}

//      LEAKS
