

#include "minishell.h"

void	ft_echo(char **args)  ///// HANDLE FD REDIRECTION
{
	int i;
	int j;
	bool n_option;
	bool flag_over;	

	i = 1;
	n_option = false;
	flag_over = false;
	while (args[i])
	{
		j = 0;
		if (ft_strncmp(&args[i][j], "-n", 2) == 0 && !flag_over)
            n_option = true;
		else
		{
			flag_over = true;
			while(args[i][j])
        		write(1, &args[i][j++], 1);
			if (args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
    if (!n_option)
        write(1, "\n", 1);
}
