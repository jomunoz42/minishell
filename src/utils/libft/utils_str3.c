

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	a;

	if (!s)
		return ;
	a = 0;
	while (s[a] != '\0')
	{
		ft_putchar_fd(s[a], fd);
		a++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	a;
	int	num;
	int	sign;

	a = 0;
	num = 0;
	sign = 1;
	while (nptr[a] == ' ' || (nptr[a] >= 9 && nptr[a] <= 13))
		a++;
	if (nptr[a] == 45 || nptr[a] == 43)
	{
		if (nptr[a] == 45)
			sign = -sign;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		num = num * 10 + (nptr[a] - '0');
		a++;
	}
	return (num * sign);
}
