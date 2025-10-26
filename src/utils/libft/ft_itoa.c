

#include "minishell.h"

static int	num_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	len = num_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
    str[0] = '/';
	str[len] = '\0';
	num = n;
	if (n == 0)
		str[1] = '0';
	while (num > 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

static void reverse(char *str, int len)
{
	int 	start;
    int 	end;
	char 	tmp;

	start = 0;
	end = len - 1;
    while (start < end)
    {
        tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

char *ft_itoa_jomunoz(int n)
{
    char *str;
    int i;
    long num;
	
	i = 0;
	num = n;
	str = malloc(12);
    if (!str)
        return NULL;
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return (str);
    }
    while (num != 0)
    {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';
    reverse(str, i);
    return (str);
}
