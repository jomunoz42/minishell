
#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	a;
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (a < len)
	{
		str[a] = s[start + a];
		a++;
	}
	return (str);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*buffer1;

	buffer1 = s;
	a = 0;
	while (a < n)
	{
		buffer1[a] = (unsigned char)c;
		a++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb >= ((size_t) - 1) / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL); 
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
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

char	*ft_strrchr(const char *s, int c)
{
	int		length;

	length = 0;
	while (s[length] != '\0')
		length++;
	while (length >= 0)
	{
		if (s[length] == (char)c)
			return ((char *)&s[length]);
		length--;
	}
	return (NULL);
}
