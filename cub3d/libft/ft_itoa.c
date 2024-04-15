/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:12:59 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/11 06:23:21 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	get_len(int n)
{
	int	len;

	len = 1;
	if (n == 0)
		return (1);
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*swap(char	*str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = (ft_strlen(str) -1);
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

static char	*convert(char *nbr, int n, int len, int sign)
{
	int	i;

	i = 0;
	while (i < len)
	{
		nbr[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	if (sign == 1)
	{
		nbr[i] = '-';
		i++;
	}
	nbr[i] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*nbr;

	if (n == INT_MIN)
	{
		nbr = malloc(sizeof(*nbr) * 12);
		if (!(nbr))
			return (NULL);
		ft_strlcpy(nbr, "-2147483648", 12);
		return (nbr);
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	len = get_len(n);
	nbr = malloc(sizeof(*nbr) * (len + 1 + sign));
	if (!(nbr))
		return (NULL);
	nbr = convert(nbr, n, len, sign);
	nbr = swap(nbr);
	return (nbr);
}
/*
int	main(void)
{
	int	n;
	char	*nbr;
	size_t	test;

	n = 0;
	nbr = ft_itoa(n);
	printf("the number is %s\n", nbr);
	test = malloc_usable_size(nbr);
	printf("malloc size is %i\n", test);
	free(nbr);
}
*/
