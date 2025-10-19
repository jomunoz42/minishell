
/* #include "minishell.h"

static void	ctrl_d_pressed(char **argv, t_pipe *get, char *line)
{
	if (!line)
	{
		write(2,
			"bash: warning: here-document delimited by end-of-file (wanted `",
			63);
		write(2, argv[2], get->length);
		write(2, "')\n", 3);
		close(get->hdoc_pipe[1]);
		get->infile = get->hdoc_pipe[0];
		get->eof_no_limiter = 1;
	}
}

static void	handling_here_doc(char **argv, t_pipe *get)
{
	char	*line;

	if (pipe(get->hdoc_pipe) == -1)
		handling_errors(argv, get, 3);
	get->length = ft_strlen(argv[2]);
	while (1)
	{
		line = get_next_line(0);
		ctrl_d_pressed(argv, get, line);
		if (get->eof_no_limiter == 1)
			break ;
		if (!*line || ((ft_strncmp(argv[2], line, get->length) == 0)
				&& line[get->length] == '\n'))
		{
			free(line);
			close(get->hdoc_pipe[1]);
			get->infile = get->hdoc_pipe[0];
			break ;
		}
		write(get->hdoc_pipe[1], line, ft_strlen(line));
		free(line);
	}
} */