

#include "minishell.h"

int    ft_pwd(t_map *env, t_exec *exec)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
    {
        path = env->get(env, "PWD");
        if (!path || path[0] == '\0')
        {
            fprintf(stderr, "bash: pwd: error retrieving current directory: getcwd: %s\n", strerror(errno));
            return (1);
        }
        write(exec->out, path, ft_strlen(path));
    }
    else
    {
        write(exec->out, path, ft_strlen(path));
        free(path);
    }
    return (0);
}

    // Possible Errors (errno)

    // EACCES: permission denied to read a directory in the path.
