

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

typedef struct s_exec
{
	int				infile;
	int				outfile;
	int				in;
	int				out;
	int				cmd_number;
	// int				child;
	int				pipefd[2];
	int				eof_no_limiter;
	pid_t			*process_id;
	int				status;

	int				env_len;
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
}					t_cmd;

//./minishell ls >> END cat < fd | wc

//========================BUILTINS========================

int					ft_echo(t_cmd *cmd, t_map *env);
int					ft_cd(t_cmd *cmd, t_map *env);
int					ft_pwd(t_map *env);
void				ft_export(t_cmd *cmd, t_map *env, t_exec *exec);
void				ft_unset(t_cmd *cmd, t_map *env, t_exec *exec);
void				ft_env(t_map *env);
void				ft_exit(int status);

//=======================EXECUTION========================

void				handle_path_not_found(char *path, char **cmd);
char				*get_absolute_path(t_map *env, char *cmd);
void				execute_command(t_cmd *cmd, t_map *env, t_exec *exec);

//========================PARSING=========================

void				parsing(char *input);
void				free_double(char **arg);

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
int					count_arguments(char **input);

//=========================LIBFT==========================

char				*ft_strdup(const char *s);
int					ft_strlen(const char *s);
char				*ft_itoa(int n);
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


# define COPY ft_strdup

#endif