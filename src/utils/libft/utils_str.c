

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*copy;

	len = ft_strlen(s);
	copy = ft_calloc((len + 1), sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[a] != '\0' || s2[a] != '\0') && a < n)
	{
		if ((unsigned char)s1[a] != (unsigned char)s2[a])
		{
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		}
		a++;
	}
	return (0);
}
