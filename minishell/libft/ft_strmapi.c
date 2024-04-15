/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 05:48:15 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:55:04 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	test(unsigned int i, char c)
{
	i++;	//just a dummy, for unused parameter error
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buf;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	buf = ft_strdup(s);
	if (!buf)
		return (NULL);
	while (buf[i] != '\0')
	{
		buf[i] = f((unsigned int)i, buf[i]);
		i++;
	}
	return (buf);
}
/*
int	main(void)
{
	char	str[] = "test";
	char	*buf;

	buf = ft_strmapi(str, &test);
	ft_putendl_fd(buf, 1);
	return (0);
}
*/
