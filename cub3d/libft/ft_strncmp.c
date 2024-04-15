/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:33:05 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 09:33:18 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (2);
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%i\n", ft_strncmp("test\200", "test\0", 6));
	printf("%i\n\n", strncmp("test\200", "test\0", 6));
	
	printf("%d\n", ft_strncmp("Hello", "Hello1",5));
	printf("%d\n\n", strncmp("Hello", "Hello1",5));
	
	printf("%d\n", ft_strncmp("Hello", "He",2));
	printf("%d\n\n", strncmp("Hello", "He",2));
	
	printf("%d\n", ft_strncmp("He", "Hello",6));
	printf("%d\n\n", strncmp("He", "Hello",6));
	
	printf("%d\n", ft_strncmp("Hello", "Hello",4));
	printf("%d\n\n", strncmp("Hello", "Hello",4));
	
}
*/