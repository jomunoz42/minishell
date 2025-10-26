#include "minishell.h"

void error_exit(char *s, int code)
{
    errno = code;
    perror(s);
    exit(0);
}

char *ft_realloc_str(char *str, int len)
{
    int i;
    char *new;

    new = malloc(len);
    if (!new)
        return(free(str), NULL);
    if (str)
    {
        ft_strlcpy(new, str, len);
        free(str);
    }
    else
        new[0] = '\0';
    return (new);
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

int	arr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
