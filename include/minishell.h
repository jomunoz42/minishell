

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_exec
{
	int				in;
	int				out;
	int				pipefd[2];
	int				status;

	bool			no_permission;
	bool			no_file;

	int				eof_no_limiter;
}					t_exec;

typedef struct s_redir
{
	char			*args[2];
	struct s_redir	*next;
	int				fd;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
	pid_t			pid;
}					t_cmd;

//./minishell ls >> END cat < fd | wc

//========================BUILTINS========================

int					ft_echo(t_cmd *cmd, t_map *env, t_exec *exec);
int					ft_cd(t_cmd *cmd, t_map *env);
int					ft_pwd(t_map *env);
void				ft_export(t_cmd *cmd, t_map *env, t_exec *exec);
void				ft_unset(t_cmd *cmd, t_map *env, t_exec *exec);
void				ft_env(t_map *env);
void				ft_exit(int status);

//=======================EXECUTION========================

char				*get_absolute_path(t_map *env, char *cmd);
int					is_built_in(t_cmd *cmd, t_map *env, t_exec *exec);
void				execute_heredocs(t_cmd *cmd, t_exec *exec);
void				execute_command(t_cmd *cmd, t_map *env, t_exec *exec);
void				handling_errors(t_exec *exec, char *arg, int error_id);
void				handle_path_not_found(char *path, char **cmd);
void				close_everything(t_exec *exec);

//========================PARSING=========================

t_cmd				*new_node(char **new, t_map *env);
t_cmd				*separate_args(t_cmd *head, char *line, t_map *env);
t_cmd				*parsing(char *input, t_cmd *all, t_map *env);
int					quote_handler(char *input);
void				revert_quote(char **line);
char				*unlink_redir(char *str);
int					count_redir(char *str);
int					init_redir(t_cmd *head);
t_redir				*new_redir(t_cmd *head, int i);
int					remove_redir(t_cmd *head, int i);
int					change_expansion(t_cmd *head, t_map *env);
void				remove_quotes(t_cmd *head);
t_redir				*redir_start(t_cmd *head, int i);

//==========================UTILS=========================

void				copy_env(t_map *map, char **env, t_exec *exec);
void				print_env(t_map *env);
int					length_of_equal(char *vars);
int					is_there_equal(char *vars);
int					is_there_value(char *vars);
int					handle_folder_errors(t_cmd *cmd, char *path);
int					file_or_directory(char *path);
void				handle_cd_errors(char *path, int error_id);
char				*find_last_slash(char *current_pwd);
char				*ft_strjoin_free(char *s1, char *s2);
void				free_double(char **arg);
void				error_exit(char *s, int code);
char				*ft_realloc_str(char *str, int len);
int					arr_count(char **arr);
char				*get_next_line(int fd);

//=========================LIBFT==========================

char				*ft_strdup(const char *s);
int					ft_strlen(const char *s);
char				**ft_split(char const *s, char c);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strrchr(const char *s, int c);
int					ft_lstsize(t_cmd *lst);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_atoi(const char *nptr);
char				*ft_itoa_jomunoz(int nbr);
char				*ft_itoa(int n);
int					ft_isalnum(int c);
int					ft_isdigit(int c);


# define COPY ft_strdup

#endif