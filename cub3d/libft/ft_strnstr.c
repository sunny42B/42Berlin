/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:45:40 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/11 07:08:19 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;
	char	*buf;

	i = 0;
	buf = (char *)big;
	needle_len = ft_strlen(little);
	if (needle_len == 0 || big == little)
		return (buf);
	while (buf[i] != '\0' && i < len)
	{
		j = 0;
		while (buf[i + j] != '\0' && little[j] != '\0'
			&& buf[i + j] == little[j] && i + j < len)
			j++;
		if (j == needle_len)
			return (&buf[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*buf;
	char	*big = "where is it";
	char	*little = "is";

	buf = ft_strnstr(big, little, 10);
	ft_putendl_fd(buf, 1);
	return (0);
}
*/