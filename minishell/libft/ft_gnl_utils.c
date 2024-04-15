/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:54:31 by fhassoun          #+#    #+#             */
/*   Updated: 2023/05/16 11:07:51 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstbuf;
	char	*srcbuf;

	i = 0;
	if (dst == src || n == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	dstbuf = (char *)dst;
	srcbuf = (char *)src;
	while (i < n)
	{
		dstbuf[i] = srcbuf[i];
		i++;
	}
	return (dst);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*rtn;

	if (!s1 || !s2)
		return (NULL);
	rtn = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (rtn == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			rtn[i] = s1[i];
	while (s2[c] != '\0')
		rtn[i++] = s2[c++];
	rtn[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (rtn);
}

/*char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	const char	*y;

	i = 0;
	y = (char *)s;
	while (y[i] != '\0')
	{
		if (y[i] == (char)c)
			return ((char *)&y[i]);
		i++;
	}
	if (y[i] == (char)c)
		return ((char *)&y[i]);
	return (NULL);
}*/

/* size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
} */

char	*ft_gnl_strdup(char *src)
{
	size_t	size;
	char	*dest;
	int		i;

	size = ft_strlen(src);
	dest = malloc(sizeof (*dest) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
