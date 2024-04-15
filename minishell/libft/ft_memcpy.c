/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:50:26 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/11 06:47:34 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

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
/*
int	main(void)
{
	char	*string = "Hello World!";
	char	tmp[20];

	ft_memcpy(tmp, string, 5);
	printf("copied '%s' into '%s'\n", string, tmp);
	return (0);
}
*/
