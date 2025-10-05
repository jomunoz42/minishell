

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../MAP/map.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct    s_built
{
   t_map          *env;
   t_map          *export;
}                 t_built;

typedef struct s_redir
{
   char             **args;
   struct s_redir   *next;
   int              fd;
}                   t_redir;

typedef struct s_cmd
{
   char           **args;
   t_redir        *redir;
   struct s_cmd   *next;
}                 t_cmd;

//./minishell ls >> END cat < fd | wc

//=========================LIBFT==========================

int		ft_strncmp(const char *s1, const char *s2, size_t n);

//========================BUILTINS========================

void	  ft_echo(char **args);
void    ft_exit( /* STRUCT */ int status);
int     ft_pwd(void);
void    ft_env(char **env);
void    ft_export(char **env, char *input);

//========================PARSING=========================

void	   parsing(char *input);
void	   free_double(char **arg);

//=========================LIBFT==========================

char	   *ft_strdup(const char *s);
int		ft_strlen(const char *s);
char	   *ft_itoa(int n);
char	   **ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	   *ft_strjoin(char const *s1, char const *s2);

#endif