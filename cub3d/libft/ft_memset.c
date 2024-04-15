/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:24 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:53:43 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*buf;

	i = 0;
	buf = (char *)s;
	while (i < n)
	{
		buf[i] = c;
		i++;
	}
	return (s);
}

/*
int	main(void)
{
	//char	*string = "teststring";
	char	string[10] = "teststring";
	char	con = 'a';

	printf("the old string is '%s'\n", string);
	ft_memset(string, con, 3);
	printf("the new string is '%s'\n", string);
	return (0);
}
*/
