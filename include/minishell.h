/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:50:25 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/25 18:01:04 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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
	bool			is_child;
	bool			msg_printed;
	bool			expand;
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

//========================BUILTINS========================

int					ft_echo(t_cmd *cmd, t_exec *exec);
int					ft_cd(t_cmd *cmd, t_map *env);
int					ft_pwd(t_map *env, t_exec *exec);
int					ft_export(t_cmd *cmd, t_map *env, t_exec *exec);
int					ft_unset(t_cmd *cmd, t_map *env);
int					ft_env(t_cmd *cmd, t_map *env, t_exec *exec);
int					ft_exit(int status, t_exec *exec, t_cmd *cmd);

//=======================EXECUTION========================

int					exec_heredocs(t_cmd *cmd, t_cmd *temp, t_exec *exec,
						t_map *env);
void				execute_command(t_cmd *cmd, t_map *env, t_exec *exec);
int					handling_errors(t_exec *exec, char *arg, int error_id,
						t_cmd *cmd);
void				handle_execve_errors(t_cmd *cmd, t_cmd *temp, t_map *env,
						t_exec *exec);
void				close_everything(t_exec *exec);
void				close_and_reset(t_exec *exec, t_cmd *cmd);
int					convert_status(int status);
void				redirections(t_redir *redir, t_exec *exec, t_cmd *cmd);
int					exit_parsing(t_cmd *cmd, t_exec *exec, t_map *env);
int					no_file_no_perm(t_cmd *cmd, t_exec *exec);

//========================PARSING=========================

t_cmd				*new_node(char **args);
t_cmd				*separate_args(t_cmd *head, char *line);
t_cmd				*parsing(char *input, t_cmd *all);
int					quote_handler(char *input, int n);
char				*unlink_redir(char *str);
int					count_redir(char *str);
int					init_redir(t_cmd *head);
t_redir				*new_redir(t_cmd *head, int i);
int					remove_redir(t_cmd *head, int i);
int					change_expansion(t_cmd *head);
void				remove_quotes(t_cmd *head);
t_redir				*redir_start(t_cmd *head, int i);
void				sig_handler(void);
void				put_error_msg(void);
void				close_fds_exit(t_cmd *cmd);

//==========================UTILS=========================

void				copy_env(t_map *map, char **env, t_exec *exec, t_cmd *cmd);
int					length_of_equal(char *vars);
int					is_there_equal(char *vars);
int					is_there_value(char *vars);
int					is_only_number(char *arg);
int					handle_cd_errors(char *path, int error_id);
int					file_or_directory(char *path, t_cmd *cmd);
char				*ft_strjoin_free(char *s1, char *s2);
void				free_double(char **arg);
char				*ft_realloc_str(char *str, int len);
int					arr_count(char **arr);
char				identify_quote(char c, char flag);
t_map				*get_map_addr(t_map *env);
t_cmd				*get_cmd_addr(t_cmd *src);
t_exec				*get_exec_addr(t_exec *src);
int					get_pid(t_exec *exec, t_cmd *cmd);
void				free_list(t_cmd *all);

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
int					ft_lstsize(t_cmd *lst);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_isalnum_modified(int c);
int					ft_atoi(const char *nptr);
char				*ft_itoa(int nbr);
int					ft_isdigit(int c);

#endif