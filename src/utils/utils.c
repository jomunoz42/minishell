#include "minishell.h"

void error_exit(char *s)
{
    perror(s);
    exit(0);
}