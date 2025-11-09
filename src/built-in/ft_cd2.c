
#include "minishell.h"

int handle_cd_errors(char *path, int error_id, t_map *env)
{
    if (error_id == 0)
    {
        fprintf(stderr, "bash: cd: error retrieving current directory: getcwd: %s\n", strerror(errno));
        return (1);
    }
    if (error_id == 1)     
    {
        write(2, "bash: cd: too many arguments\n", 30);
        return (1);
    }
    write(2, "bash: cd: ", 11);
    if (path)
        write(2, path, ft_strlen(path));
    if (error_id == 2)            
        (write(2, ": No such file or directory\n", 29));
    else if (error_id == 3)   
        (write(2, ": Not a directory\n", 19));
    else if (error_id == 4)   
        (write(2, ": Permission denied\n", 21));
    return (1);
}

int file_or_directory(char *path, t_map *env, t_cmd *cmd)
{
    struct stat buf;
    
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
        {
            if (cmd->args[1][0] == '/')
                return (handle_cd_errors(path, 2, env));
            else
                return (handle_cd_errors(cmd->args[1], 2, env));
        }
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
        perror("bash: cd");
}

int handle_cd_options(t_cmd *cmd, t_map *env, char *current_pwd)
{
    int i;

    i = 1;
    if (!ft_strncmp(cmd->args[1], "-P", 3) || !ft_strncmp(cmd->args[1], "-L", 3))
    {
        write(2, "Minishell subject: cd with only a relative or absolute path\n", 61);
        free(current_pwd);
        return (1);
    }
    else
    {
        while(cmd->args[1][i] && (cmd->args[1][i] == 'P' || cmd->args[1][i] == 'L'))
            i++;
        write(2, "bash: cd: -", 11);
		write(2, &cmd->args[1][i], 1);
		write(2, ": invalid option\n", 18); 
        write(2, "cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 41);
        free(current_pwd);
        return (2);
    }
}

int    goes_nowhere(t_map *env, char *current_pwd)
{
    if (chdir(current_pwd) != 0)
    {
        if (errno == EACCES)
            handle_cd_errors(".", 4, env);
        else if (errno == ENOENT)
            handle_cd_errors(".", 2, env);
        return (1);
    }
    free(current_pwd);
    return (0);
}
