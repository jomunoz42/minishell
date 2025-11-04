

#include "minishell.h"

static int	only_ns(char *arg)
{
	int	j;

	j = 1;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd, t_map *env, t_exec *exec)
{
	int		i;
	int		j;
	bool	n_option;
	bool	over;

	i = 0;
	n_option = false;
	over = false;
	printf("%d\n", exec->out);
	while (cmd->args[++i])
	{
		j = 0;
		if (!ft_strncmp(&cmd->args[i][j], "-n", 2) && !over && only_ns(cmd->args[i]))
			n_option = true;
		else
		{
			over = true;
			while (cmd->args[i][j])
				write(exec->out, &cmd->args[i][j++], 1);
			if (cmd->args[i + 1])
				write(exec->out, " ", 1);
		}
	}
	if (!n_option)
		write(exec->out, "\n", 1);
	env->put(env, "?", ft_strdup("0"));
}

///// HANDLE FD REDIRECTION