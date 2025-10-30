

#include "minishell.h"

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

char *ft_itoa(int n)
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
