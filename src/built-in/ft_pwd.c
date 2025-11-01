

#include "minishell.h"

void    ft_pwd(t_map *env)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
    {
        path = env->get(env, "PWD");
        if (!path || path[0] == '\0')
        {
            fprintf(stderr, "bash: pwd: error retrieving current directory: getcwd: %s\n", strerror(errno));
            env->put(env, "?", ft_strdup("1"));
            return ;
        }
        printf("%s\n", path);
    }
    else
    {
        printf("%s\n", path);
        free(path);
        env->put(env, "?", ft_strdup("0"));
    }
}

    // Possible Errors (errno)

    // EACCES: permission denied to read a directory in the path.

