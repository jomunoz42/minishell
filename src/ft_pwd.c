/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:09:29 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/03 23:26:25 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_pwd()
{
    char    *path;

    path = getcwd(NULL, 0);
    if (path == NULL)
    {
        perror("pwd error:");
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}

    // Possible Errors (errno)

    // EINVAL: size is 0.

    // ERANGE: buffer size is too small for the pathname.

    // EACCES: permission denied to read a directory in the path.

    // ENOMEM: insufficient memory (if dynamically allocating).
