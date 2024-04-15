/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 06:58:04 by fhassoun          #+#    #+#             */
/*   Updated: 2023/03/18 06:12:30 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*dest;
	int		i;

	size = ft_strlen(src);
	dest = malloc(sizeof (*dest) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char *dest[100];

	*dest = ft_strdup("xIeyr4lEO5xnT8XKhprwEP6etvp0U");
	ft_putstr_fd(*dest, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}*/
