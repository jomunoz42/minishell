

#include "minishell.h"

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (d > s && d <= s + n)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d);
}