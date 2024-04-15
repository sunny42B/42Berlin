/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:42:38 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 09:36:14 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*buf;

	i = 0;
	buf = (char *)s;
	while (i < n)
	{
		buf[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	str[10] = "teststring";

	ft_bzero(str + 3, 3);
	printf("the new string is '%s'\n", str);
	return (0);
}
*/
