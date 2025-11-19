/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:25:34 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/19 19:35:08 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_size(const char *s)
{
	size_t	a;

	a = 0;
	if (!s)
		return (0);
	while (s[a])
	{
		if (s[a++] == '\n')
			break ;
	}
	return (a);
}

static int	if_new_line_exists(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

static void	get_the_rest(char *buffer)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (buffer[a] && buffer[a] != '\n')
		a++;
	if (buffer[a] == '\n')
		a++;
	while (buffer[a])
		buffer[b++] = buffer[a++];
	buffer[b] = '\0';
}

static char	*copy_to_line(char *line, char *buffer)
{
	char	*new_line;
	char	*temp;
	char	*to_free;

	new_line = malloc(get_size(buffer) + get_size(line) + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	temp = new_line;
	to_free = line;
	while (line && *line)
		*temp++ = *line++;
	while (*buffer)
	{
		*temp++ = *buffer;
		if (*buffer++ == '\n')
			break ;
	}
	free(to_free);
	*temp = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		readbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	readbytes = 1;
	while (!if_new_line_exists(line))
	{
		if (*buffer == '\0')
		{
			readbytes = read(fd, buffer, BUFFER_SIZE);
			if (readbytes == -1)
				return (free(line), NULL);
			if (readbytes >= 0)
				buffer[readbytes] = '\0';
			if (readbytes == 0)
				return (line);
		}
		line = copy_to_line(line, buffer);
		get_the_rest(buffer);
	}
	return (line);
}
