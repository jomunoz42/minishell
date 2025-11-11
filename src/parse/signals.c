#include "minishell.h"

void	handler(int sig)
{
	t_map	*env;

	env = get_map_addr(NULL);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
        env->put(env, "?", ft_strdup("130"));
	}
	// else if (sig == SIGSEGV)
	//     ft_exit(0);
}

void	sig_handler(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
