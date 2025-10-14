/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:27:53 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/14 23:35:09 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char  *root_edge_case(char *path, char *new_path, int index)
{
    if (index == 0)
    {
        if (path[0] == '/')
        {
            new_path = malloc(2);
            if (!new_path)
                ft_exit(1);
            new_path[0] = '/';
            new_path[1] = '\0';
            return (new_path);
        }
        else
            return (NULL);
    }
    else
        return (NULL);
}

static char  *find_last_slash(char *path)
{
    char *new_path;
    int i;

    i = 0;
    while(path[i])
        i++;
    while (i > 0 && path[i] != '/')
        i--;
    root_edge_case(path, new_path, i);
    new_path = malloc(sizeof(char) * (i + 1));
    if (!new_path)
        ft_exit(1);
    ft_strlcpy(new_path, path, i + 1);
    new_path[i] = '\0';
    return (new_path);
}

static void not_valid_directory(char *path, int error_id)
{
    write(2, "bash: cd: ", 11);
    if (error_id == 1)                               //  too many arguments
    {
        write(2, "too many arguments\n", 20);
        return ;
    }
    write(2, path, ft_strlen(path));
    if (error_id == 2)                               // does not exist
        write(2, ": No such file or directory\n", 29);
    else if (error_id == 3)                          // is a file
        write(2, ": Not a directory\n", 19);
    else if (error_id == 4)                          // permission denied
        write(2, ": Permission denied\n", 21);
}

int file_or_directory(char *path)
{
    struct stat buf;
    
    if (stat(path, &buf) != 0) 
    {
        if (errno == ENOENT)
            return (not_valid_directory(path, 2), 1);
    }
    else if (S_ISREG(buf.st_mode))
        return (not_valid_directory(path, 3), 1);
    if (S_ISDIR(buf.st_mode)) 
        return (0);
    return (1);
}

static int handle_folder_errors(t_cmd *cmd, char *path)
{
    if (errno == EACCES)
    {
        if (cmd->args[1][0] == '/')
            return (not_valid_directory(path, 4), 1);
        else
            return (not_valid_directory(cmd->args[1], 4), 1);
    }
    else
        return (perror("bash: cd"), 1);
}

// static void    ft_cd_util2(t_cmd *cmd, t_map *env)
// {
//     char *path;
    
//     if (!ft_strncmp(cmd->args[1], "-", 2))
//     {
//         path = getenv("OLDPWD");
//         if (!path)
//             write(2, "bash: cd: OLDPWD not set\n", 24);
//         else
//         {
//             if (chdir(path) == 0)
//                 printf("%s\n", path);
//             else
//                 not_valid_directory(path, 1);  // still need handle
//         }
//     }
//     if (!ft_strncmp(cmd->args[1], "..", 3))
//     {
//         path = getcwd(NULL, 0);
//         path = find_last_slash(path);
//         chdir(path);
//     }
//     if (!ft_strncmp(cmd->args[1], ".", 2))
//         return (0);
// }

static int    ft_cd_util1(t_cmd *cmd, t_map *env, char *old_pwd)
{
    char *path;
    
    if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
    {
        path = env->get(env, "HOME");
        if (!path)
            return (write(2, "bash: cd: HOME not set\n", 24), 1);
        if (file_or_directory(path) == 0)
        {
            if (chdir(path) != 0)
                handle_folder_errors(cmd, path);
            env->put(env, "OLDPWD", old_pwd);
            env->put(env, "PWD", path);
            return (0);
        }
    }
    return (0);
}

int	ft_cd(t_cmd *cmd, t_map *env)  /// SEE RETURN VALUES   &&  CHECK ALLOCS FAILURE
{
    char    *path;
    char    *old_pwd;

    old_pwd = getcwd(NULL, 0);
    if (cmd->args[2])
        return (not_valid_directory(NULL, 1), 1);
    if (ft_cd_util1(cmd, env, old_pwd))
        return (1);
    // ft_cd_util2(cmd, env);
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
            handle_folder_errors(cmd, path);
        env->put(env, "OLDPWD", old_pwd);
        env->put(env, "PWD", path);
        return (0);
    }
    else
        return (1);
    return (0);
}


    //  WHY    OLDPWD=/home/jomunoz/Common_Core_42     AT BEGINNING?
    

    // int chdir(const char *path);     0 on success, -1 on error

    // int stat(const char *pathname, struct stat *statbuf);     0 on success, -1 on error
    // contains size, type, permissions, modification dates, file type


    // Parsing cd arguments (handle no argument, ~, -, or path).
    // cd      cd ~      cd -      cd ..     cd /Com...       cd . (does nothing)

    // Using chdir to attempt directory change.

    // On success, update OLDPWD and PWD.

    // On failure, print an error message.


    // bash: cd: (%s): No such file or directory
