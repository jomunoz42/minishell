

#include "minishell.h"

static void handle_cd_errors(char *path, int error_id)
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

static int handle_folder_errors(t_cmd *cmd, char *path)
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
    else
        return (1);
    return (0);   // check this
}

// check cd - cd - and then cd (its seg faulting) && SEE RETURN VALUES &&  CHECK ALLOCS FAILURE
int	ft_cd(t_cmd *cmd, t_map *env)
{
    char    *path;
    char    *current_pwd;

    current_pwd = getcwd(NULL, 0);
    // {
    //     if (!current_pwd)
    //     {
    //         current_pwd = env->get(env, "PWD");
    //         if (!current_pwd || current_pwd[0] == '\0')
    //             return (handle_cd_errors(NULL, 0), 1);
    //     }
    // }
    if (cmd->args[1] && cmd->args[2])
        return (handle_cd_errors(NULL, 1), 1);
    else if (goes_home(cmd, env, current_pwd))
        return (1);
    else if (goes_last_dir(cmd, env, current_pwd))
        return (1);
    else if (goes_up(cmd, env, current_pwd))
        return (1);
    else if(absolute_or_relative(cmd, env, current_pwd))
        return (1);
    return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int		length;

	length = 0;
	while (s[length] != '\0')
		length++;
	while (length >= 0)
	{
		if (s[length] == (char)c)
			return ((char *)&s[length]);
		length--;
	}
	return (NULL);
}