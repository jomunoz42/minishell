

#include "minishell.h"

int    ft_pwd(t_map *env)
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
        printf("%s\n", path);
    }
    else
    {
        printf("%s\n", path);
        free(path);
    }
    return (0);
}

    // Possible Errors (errno)

    // EINVAL: size is 0.

    // ERANGE: buffer size is too small for the pathname.

    // EACCES: permission denied to read a directory in the path.

    // ENOMEM: insufficient memory (if dynamically allocating).
