#include "minishell.h"

void handler(int sig)
{
    if (sig == SIGINT)
        rl_done = 1;

}

void	sig_handler(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}