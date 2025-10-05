

#include "minishell.h"

void parsing(char *input, char **env)
{
	int i;
	char **line;
	char **args;

	if (!input || !env || !*env)
		ft_exit(1);
	line = ft_split(input, '|');
	if (!line)
		ft_exit(1);
	i = 0;
	int j;
	while (line[i])
	{
		args = ft_split(line[i], ' ');
		if (!args)
			ft_exit(0);
		j = 0;
		while(args[j])
			printf("new args: %s\n", args[j++]);
		free_double(args);
		i++;
	}
	i = 0;
	while(line[i])
		printf("line: %s\n", line[i++]);
}
