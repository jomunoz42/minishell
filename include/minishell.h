/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:30:26 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/03 22:24:12 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../MAP/map.h"


typedef struct s_redir
{
   char             **args;
   struct s_redir   *next;
   int              fd;
} t_redir;


typedef struct s_cmd
{
   char           **args;
   t_redir        *redir;
   struct s_cmd   *next;
} t_cmd;

//./minishell ls >> END -la < t | wc

//=========================LIBFT==========================

int	ft_strncmp(const char *s1, const char *s2, size_t n);

//========================BUILTINS========================

int echo(char **args);

#endif