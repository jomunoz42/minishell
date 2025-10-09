

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
   t_map          *env_exported;
   t_map          *export;
   t_map          *exported;
   int            export_len;
   int            exported_len;
   char           **input;
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

int     ft_pwd(void);
void    ft_export(t_built *built, char **env);
void    ft_unset(t_built *built);
void    ft_env(t_built *built, char **env);
void    ft_exit( /* STRUCT */ int status);

//==========BUILTINS_UTILS=========

int   len_after_equal(char *vars);
int   many_equals(char *vars);
void  remove_extra_vars(t_built *built);
int   count_arguments(char **input);

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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

#endif