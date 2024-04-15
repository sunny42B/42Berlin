/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 09:01:38 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:53:38 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstbuf;
	char	*srcbuf;

	dstbuf = (char *)dst;
	srcbuf = (char *)src;
	i = -1;
	if ((dst == NULL && src == NULL) || n == 0)
		return (dst);
	if (dst > src)
	{
		while (++i < n)
			dstbuf[n - 1 - i] = srcbuf[n - 1 - i];
	}
	else
	{
		while (++i < n)
			dstbuf[i] = srcbuf[i];
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
