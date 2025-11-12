#include "minishell.h"

void	handler(int sig)
{
	t_map	*env;

	(void)sig;
	env = get_map_addr(NULL);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	env->put(env, "?", ft_strdup("130"));
}

void	sig_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}
