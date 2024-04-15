/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:53:39 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/10 06:08:45 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	size_t	len;

	len = nmemb * size;
	tmp = malloc(len);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, len);
	return (tmp);
}
/*
int		main(void)
{
	char	*str;

	str = (char *)ft_calloc(30, 1);
	if (!str)
		write(1, "NULL", 4);
	else
		write(1, str, 30);
	return (0);
}
*/