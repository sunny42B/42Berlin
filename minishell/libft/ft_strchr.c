/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:27:19 by fhassoun          #+#    #+#             */
/*   Updated: 2023/06/20 08:30:41 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
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
}
/*
int	main(void)
{
	char	str[] = "teste";
	char	c = '\0';
	char	*res;

	res = ft_strchr(str, c);
	printf("string after ( %c ) is ( %s )\n", c, res);
	return (0);
}
*/
