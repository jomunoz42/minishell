

#include "minishell.h"

static int only_ns(char *arg)
{
	int j;

	j = 1;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, t_map *env, t_exec *exec)
{
	int i;
	int j;
	bool n_option;
	bool flag_over;	

	i = 1;
	n_option = false;
	flag_over = false;
	while (cmd->args[i])
	{
		j = 0;
		if (ft_strncmp(&cmd->args[i][j], "-n", 2) == 0 && !flag_over && only_ns(cmd->args[i]))
            n_option = true;
		else
		{
			flag_over = true;
			while(cmd->args[i][j])
			{
				if (ft_strncmp(&cmd->args[i][j], "$?", 2) == 0)
				{
					printf("%d", exec->status);
					j = j + 2;
				}
				else
        			write(1, &cmd->args[i][j++], 1);
			}
			if (cmd->args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
    if (!n_option)
        write(1, "\n", 1);
	return (0);
}

///// HANDLE FD REDIRECTION