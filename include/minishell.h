

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

typedef struct s_list
{
   t_cmd *head;
   t_cmd *tail;
} t_list;

//./minishell ls >> END -la < t | wc

//=========================LIBFT==========================

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	   *ft_strdup(const char *s);
int		ft_strlen(const char *s);
char	   *ft_itoa(int n);
char	   **ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

//========================BUILTINS========================

int		echo(char **args);
int		ft_pwd(void);
void     ft_exit(int status);

//========================PARSING=========================

void	   parsing(char *input, t_cmd *all);
void	   free_double(char **arg);
int      get_absolute_path(char **env, char *cmd);
t_cmd    *new_node(char **new);
t_cmd	   *new_head();
void     put_in(char **new, t_cmd *head);
t_cmd    *new_node(char **new);
void     quote_handler(char *input);
void     revert_quote(char **line);
int      check_redir(char *str);
t_redir     *find_redir(t_cmd *head);

#endif