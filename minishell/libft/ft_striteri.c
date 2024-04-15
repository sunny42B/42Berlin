/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 06:45:31 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/09 14:54:02 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	test(unsigned int i, char *c)
{
	i++;	//just a dummy, for unused parameter error
	if (*c >= (char)'a' && *c <= (char)'z')
		*c = *c - 32;
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

/*
int	main(void)
{
	char	str[] = "test";
	char	*buf;

	ft_striteri(str, &test);
	ft_putendl_fd(buf, 1);
	return (0);
}
*/
