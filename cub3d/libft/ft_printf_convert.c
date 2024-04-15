/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:45:49 by fhassoun          #+#    #+#             */
/*   Updated: 2023/01/03 07:38:04 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include "libft.h"

int	print_hex(unsigned int value, char var)
{
	char	*hex_digits;
	char	*buf;
	int		len;
	int		i;

	hex_digits = "0123456789abcdef";
	i = 0;
	buf = ft_calloc(100, sizeof(*buf));
	if (!buf)
		return (0);
	while (value > 0)
	{
		buf[i] = hex_digits[value % 16];
		value = value / 16;
		i++;
	}
	if (i == 0)
		buf[i] = '0';
	buf[i + 1] = '\0';
	buf = ft_swap(buf, i, var);
	len = print_str(buf);
	free(buf);
	return (len);
}

int	print_ptr(unsigned long long value, char var)
{
	char	*hex_digits;
	char	*buf;
	int		len;
	int		i;

	len = 0;
	hex_digits = "0123456789abcdef";
	i = 0;
	buf = ft_calloc(100, sizeof(*buf));
	while (value > 0)
	{
		buf[i++] = hex_digits[value % 16];
		value = value / 16;
	}
	if (i == 0)
	{
		free (buf);
		return (write(1, "(nil)", 5));
	}
	buf[i + 1] = '\0';
	buf = ft_swap(buf, i, var);
	len = len + write(1, "0x", 2);
	len = len + print_str(buf);
	free(buf);
	return (len);
}

char	*ft_swap(char *buf, int i, char var)
{
	char	tmp;
	int		j;

	j = 0;
	while (j < i)
	{
		tmp = buf[j];
		buf[j] = buf[i - 1];
		buf[i - 1] = tmp;
		j++;
		i--;
	}
	if (var == 'X')
	{
		i = 0;
		while (buf[i] != '\0')
		{
			buf[i] = ft_toupper(buf[i]);
			i++;
		}
	}
	return (buf);
}

int	print_ull(unsigned int value, char var)
{
	char	*hex_digits;
	char	*buf;
	int		len;
	int		i;

	len = 0;
	hex_digits = "0123456789";
	i = 0;
	buf = ft_calloc(100, sizeof(*buf));
	if (!buf)
		return (0);
	while (value > 0)
	{
		buf[i++] = hex_digits[value % 10];
		value = value / 10;
	}
	if (i == 0)
		buf[i] = '0';
	buf[i + 1] = '\0';
	buf = ft_swap(buf, i, var);
	len = len + print_str(buf);
	free(buf);
	return (len);
}
