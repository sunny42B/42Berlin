/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:37:12 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/09 13:23:34 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	int			x;
	const char	*y;

	i = 0;
	x = 0;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			y = &s[i];
			x++;
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	if (x == 0)
		return (NULL);
	return ((char *)y);
}
/*
int	main(void)
{
	char	str[] = "teststring";
	char	c = 't';
	char	*res;

	res = ft_strrchr(str, c);
	printf("string after last ( %c ) is ( %s )\n", c, res);
	return (0);
}*/
