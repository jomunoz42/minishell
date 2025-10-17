

#include "minishell.h"

int	ft_echo(t_cmd *cmd, t_map *env)  ///// HANDLE FD REDIRECTION
{
	int i;
	int j;
	bool n_option;
	bool flag_over;	

	i = 1;
	n_option = false;
	flag_over = false;
	if (cmd->args[i] && cmd->args[i][0] == '$')
		return (printf("%s\n", env->get(env, &cmd->args[i][i])), 0);
	while (cmd->args[i])
	{
		j = 0;
		if (ft_strncmp(&cmd->args[i][j], "-n", 2) == 0 && !flag_over)
            n_option = true;
		else
		{
			flag_over = true;
			while(cmd->args[i][j])
        		write(1, &cmd->args[i][j++], 1);
			if (cmd->args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
    if (!n_option)
        write(1, "\n", 1);
	return (0);
}
