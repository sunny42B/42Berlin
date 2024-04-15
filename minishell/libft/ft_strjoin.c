/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:27:47 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:54:42 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buf = malloc(sizeof(*buf) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buf)
		return (NULL);
	while (s1[i] != '\0')
	{
		buf[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		buf[i] = s2[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
}
/*
int	main(void)
{
	char	*s1 = "test";
	char	*s2 = "string";
	char	*res;

	res = ft_strjoin(s1, s2);
	printf("the joined string is %s", res);
	free (res);
	return (0);
}
*/