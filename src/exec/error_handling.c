
#include "minishell.h"

void	handling_errors(t_exec *exec, char *arg, int error_id)
{
	if (error_id == 1)
	{
		write(2, "bash: ", 6);
		perror(arg);
	}
	if (error_id == 2)
	{
		write(2, "bash: ", 6);
		perror(arg);
	}
	if (errno == ENOENT) 
		exec->no_file = true;
	else if (errno == EACCES)
		exec->no_permission = true;
	if (error_id == 3)
	{
		perror("pipe");
		close_everything(exec); // check
		exit(1);                // free everything
	}
	if (error_id == 4)
	{
		perror("fork");
		close_everything(exec); // check
		exit(1);                // free everything
	}
}

static int   is_there_slash(char *path)
{
	int i;

	i = 0;
	if (!path)
		return (0);
	while(path[i])
	{
		if (path[i++] == '/')
			return (1);
	}
	return (0);
}

static void	 error_messages(char *path)
{
	struct stat buf;
    
	write(2, "bash: ", 6);
	write(2, path, ft_strlen(path));
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
        {
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
    }
    else if (S_ISREG(buf.st_mode))
    {
		write(2, ": Permission denied\n", 21);
		exit(126);
	}
    else if (S_ISDIR(buf.st_mode))
	{
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
}

void	handle_path_not_found(char *path, char **cmd)
{
	if (is_there_slash(path))
		error_messages(path);
	else
	{
		if (path && ft_strncmp(path, "\"\"", 1) == 0)   //  "" > 2.txt
			write(2, "Command '' not found\n", 22);
		else
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 21);
		}
		if (path && path != cmd[0] && path[0] != '\0')
			free(path);
		free_double(cmd);
		exit(127);
	}
}

void	close_everything(t_exec *exec)
{
	if (exec->in != -1)
		close(exec->in);
	if (exec->out != -1)
		close(exec->out);
} 