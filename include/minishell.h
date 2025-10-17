

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
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


typedef struct s_redir
{
   char             *args[2];
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

//========================BUILTINS========================

void	  ft_echo(t_cmd *cmd);
int     ft_pwd(void);
void    ft_export(t_cmd *cmd, t_map *env);
void    ft_unset(t_cmd *cmd, t_map *env);
void    ft_env(t_map *env);
void    ft_exit(int status);

//==========BUILTINS_UTILS=========

int   length_of_equal(char *vars);
int   is_there_equal(char *vars);
int   is_there_value(char *vars);

//=======================EXECUTION========================

void    copy_env(t_map *map, char **env);
void    print_env(t_map *env);

//========================PARSING=========================

t_cmd	   *new_head();
t_cmd    *new_node(char **new);
t_cmd    *put_in(char **new, t_cmd *head);
t_cmd	   *parsing(char *input, t_cmd *all);
void     quote_handler(char *input);
void     revert_quote(char **line);
char     *unlink_redir(char *str);
int      count_redir(char *str);

//=========================UTILS==========================


void	   *ft_memmove(void *dest, const void *src, size_t n);
char	   *ft_strdup(const char *s);
int		ft_strlen(const char *s);
char	   *ft_itoa(int n);
char	   **ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	   *ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	   *ft_substr(char const *s, unsigned int start, size_t len);
void	   *ft_calloc(size_t nmemb, size_t size);
void	   free_double(char **arg);
void     error_exit(char *s, int code);
char     *ft_realloc(char *str, int len);

#define COPY ft_strdup

#endif