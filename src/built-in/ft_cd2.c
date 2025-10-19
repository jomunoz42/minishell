
#include "minishell.h"

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

void handle_cd_errors(char *path, int error_id)
{
    if (error_id == 0)
    {
        fprintf(stderr, "bash: cd: error retrieving current directory: getcwd: %s\n", strerror(errno));
        return ;
    }
    if (error_id == 1)     
    {
        write(2, "bash: cd: too many arguments\n", 30);
        return ;
    }
    write(2, "bash: cd: ", 11);
    if (path)
        write(2, path, ft_strlen(path));
    if (error_id == 2)            
        write(2, ": No such file or directory\n", 29);
    else if (error_id == 3)   
        write(2, ": Not a directory\n", 19);
    else if (error_id == 4)   
        write(2, ": Permission denied\n", 21);
}

int file_or_directory(char *path)
{
    struct stat buf;
    
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
            return (handle_cd_errors(path, 2), 1);
    }
    else if (S_ISREG(buf.st_mode))
        return (handle_cd_errors(path, 3), 1);
    if (S_ISDIR(buf.st_mode)) 
        return (0);
    return (1);
}

int handle_folder_errors(t_cmd *cmd, char *path)
{
    if (errno == EACCES)
    {
        if (cmd->args[1][0] == '/')
            return (handle_cd_errors(path, 4), 1);
        else
            return (handle_cd_errors(cmd->args[1], 4), 1);
    }
    else
        return (perror("bash: cd"), 1);
}
