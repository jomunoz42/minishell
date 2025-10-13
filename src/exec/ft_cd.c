/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:27:53 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/13 23:29:16 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char  *find_last_slash(char *path)
// {
//     char *new_path;
//     int i;

//     i = 0;
//     while(path[i])
//         i++;
//     while (i > 0 && path[i] != '/')
//         i--;
//     if (i == 0 && path[0] != '/')
//         return NULL;
//     new_path = malloc(sizeof(char) * (i + 1));
//     if (!new_path)
//         ft_exit(1);
//     ft_strlcpy(new_path, path, i + 1);
//     new_path[i] = '\0';
//     return (new_path);
// }

static char  *find_last_slash(char *path)
{
    char *new_path;
    int i;

    i = 0;
    while(path[i])
        i++;
    while (i > 0 && path[i] != '/')
        i--;
    if (i == 0)
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
            return NULL;
    }
    new_path = malloc(sizeof(char) * (i + 1));
    if (!new_path)
        ft_exit(1);
    ft_strlcpy(new_path, path, i + 1);
    new_path[i] = '\0';
    return (new_path);
}

// DEAL WITH    NOT A DIRECTOY  (WHEN IS A FILE)
 
static void not_valid_directory(char *path)
{
    write(2, "bash: cd: ", 11);
    write(2, &path, ft_strlen(path));
    write(1, ": No such file or directory\n", 29);
}

void    ft_cd_util1(t_cmd *cmd, char *path)
{
    if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
    {
        path = getenv("HOME");
        if (!path)
            write(2, "bash: cd: HOME not set\n", 24);
        else if (chdir(path) != 0)
            not_valid_directory(path);
    }
    if (!ft_strncmp(cmd->args[1], "-", 2))
    {
        path = getenv("OLDPWD");
        if (!path)
            write(2, "bash: cd: OLDPWD not set\n", 24);
        else
        {
            if (chdir(path) == 0)
                printf("%s\n", path);
            else
                not_valid_directory(path);
        }
    }
}

void	ft_cd(t_cmd *cmd)
{
    struct  stat buf;
    char    *path;
    int     i;

    i = 0;
    if (!ft_strncmp(cmd->args[1], "..", 3))
    {
        path = getcwd(NULL, 0);
        path = find_last_slash(path);
        chdir(path);
    }
    if (!ft_strncmp(cmd->args[1], ".", 2))
        return ;

    // if (!ft_strncmp(cmd->args[1], , 2)) check if it is accessable within the system

    // else if (cmd->args[1][0] != "~" && cmd->args[1][0] != "-")
        
}

    // int chdir(const char *path);     0 on success, -1 on error

    // char *getenv(const char *name);
    // Returns pointer to the value, NULL if the variable does not exist.

    // int stat(const char *pathname, struct stat *statbuf);     0 on success, -1 on error
    // contains size, type, permissions, modification dates, file type


    
    //     chdir	      Change current working directory
    //     getcwd         Retrieve current working directory path
    //     getenv         Get environment variable values (e.g., to get HOME path)
    //     printf         Print errors or info messages to standard output
    //     access         Check existence or permissions of target directory
    //     stat	          Obtain file status information (can check if path is dir)



    // Parsing cd arguments (handle no argument, ~, -, or path).
    // cd      cd ~      cd -      cd ..     cd /Com...       cd . (does nothing)

    // Using chdir to attempt directory change.

    // On success, update OLDPWD and PWD.

    // On failure, print an error message.


    // bash: cd: (%s): No such file or directory
