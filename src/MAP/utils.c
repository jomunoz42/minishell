/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:33:05 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/04 17:48:03 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_s(char **str);

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (dest_len >= size)
		return (src_len + size);
	i = 0;
	j = dest_len;
	while (i < size - dest_len - 1 && src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest_len + src_len);
}

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, size + 1);
	ft_strlcat(str, (char *)s2, size + 1);
	return (str);
}

char	**to_str_util(char **str, t_node *node)
{
	int		i;
	char	*tmp;

	i = 0;
	while (node)
	{
		if (node->value)
		{
			tmp = ft_strjoin(node->key, "=");
			str[i] = ft_strjoin(tmp, node->value);
			free(tmp);
		}
		else
			str[i] = ft_strjoin(node->key, "");
		if (!str[i])
			return (free_s(str), NULL);
		node = node->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
