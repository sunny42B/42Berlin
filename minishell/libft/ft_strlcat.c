/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 05:16:59 by fhassoun          #+#    #+#             */
/*   Updated: 2023/03/18 07:04:47 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(dst);
	if (size <= len)
		return (ft_strlen(src) + size);
	while (src[i] != '\0' && (len + i) < (size - 1))
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (ft_strlen(src) + len);
}
/*
int	main(void)
{
	const char	src[] = "string";
	char		dst[] = "test";
	size_t		l;

	l = ft_strlcat(dst, src, 11);
	printf("the new length is %li\n", l);
	printf("the new string is %s\n ", dst);
	return (0);
}*/
