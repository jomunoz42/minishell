
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

int	ft_isalnum(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
