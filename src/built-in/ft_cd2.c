
#include "minishell.h"

void handle_cd_errors(char *path, int error_id, t_map *env)
{
    if (error_id == 0)
    {
        fprintf(stderr, "bash: cd: error retrieving current directory: getcwd: %s\n", strerror(errno));
        env->put(env, "?", ft_strdup("1"));
        return ;
    }
    if (error_id == 1)     
    {
        write(2, "bash: cd: too many arguments\n", 30);
        env->put(env, "?", ft_strdup("1"));
        return ;
    }
    write(2, "bash: cd: ", 11);
    if (path)
        write(2, path, ft_strlen(path));
    if (error_id == 2)            
        (write(2, ": No such file or directory\n", 29), env->put(env, "?", ft_strdup("1")));
    else if (error_id == 3)   
        (write(2, ": Not a directory\n", 19), env->put(env, "?", ft_strdup("1")));
    else if (error_id == 4)   
        (write(2, ": Permission denied\n", 21), env->put(env, "?", ft_strdup("1")));
}

int file_or_directory(char *path, t_map *env)
{
    struct stat buf;
    
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
            return (handle_cd_errors(path, 2, env), 1);
    }
    else if (S_ISREG(buf.st_mode))
        return (handle_cd_errors(path, 3, env), 1);
    if (S_ISDIR(buf.st_mode)) 
        return (0);
    return (1);
}

void handle_folder_errors(t_cmd *cmd, char *path, t_map *env)
{
    if (errno == EACCES)
    {
        if (cmd->args[1][0] == '/')
            handle_cd_errors(path, 4, env);
        else
            handle_cd_errors(cmd->args[1], 4, env);
    }
    else
    {
        perror("bash: cd");
        env->put(env, "?", ft_strdup("1"));
    }
}

void handle_cd_options(t_cmd *cmd, t_map *env)
{
    int i;

    i = 1;
    if (!ft_strncmp(cmd->args[1], "-P", 3) || !ft_strncmp(cmd->args[1], "-L", 3))
    {
        write(1, "Minishell subject: cd with only a relative or absolute path\n", 61);
        env->put(env, "?", ft_strdup("0"));
    }
    else
    {
        while(cmd->args[1][i] && (cmd->args[1][i] == 'P' || cmd->args[1][i] == 'L'))
            i++;
        write(2, "bash: cd: -", 11);
		write(2, &cmd->args[1][i], 1);
		write(2, ": invalid option\n", 18); 
        write(2, "cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 41);
        env->put(env, "?", ft_strdup("2"));
    }
}

void    goes_nowhere(t_map *env, char *current_pwd)
{
    if (chdir(current_pwd) != 0)
    {
        if (errno == EACCES)
            handle_cd_errors(".", 4, env);
        else if (errno == ENOENT)
            handle_cd_errors(".", 2, env);
        return ;
    }
    env->put(env, "?", ft_strdup("0"));
}
