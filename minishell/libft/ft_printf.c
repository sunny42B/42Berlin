/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:31:43 by fhassoun          #+#    #+#             */
/*   Updated: 2023/01/03 07:37:49 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include "libft.h"
//#include <stdio.h>

int	var_find(char var, va_list lst)
{
	int	len;

	len = 0;
	if (var == 'c')
		len = len + print_char(va_arg(lst, int));
	else if (var == 's')
		len = len + print_str(va_arg(lst, char *));
	else if (var == 'i' || var == 'd')
		len = len + print_nbr(va_arg(lst, int));
	else if (var == 'p')
		len = len + print_ptr(va_arg(lst, unsigned long long), var);
	else if (var == 'u')
	{
		len = len + print_ull(va_arg(lst, unsigned int), var);
	}
	else if (var == 'x' || var == 'X')
		len = len + print_hex(va_arg(lst, unsigned int), var);
	else if (var == '%')
		len = len + print_perc(var);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		i;
	int		len;

	va_start(lst, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			len = len + var_find(str[i + 1], lst);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			len++;
		}
		i++;
	}
	va_end(lst);
	return (len);
}

// int	main(void)
// {
// 	int		len;
// 	//char *p = NULL;
// 	unsigned int u = -1;
// 	len = 0;
// 	ft_printf("ptr is: %u\n", u);
// 	printf("ptr is: %u\n", u);
// 	// printf("ptr is: %p\n", -1);
// 	ft_putnbr_fd(len, 1); // print length of output string
// 	write(1, "\n", 1);
// 	return (0);
// } 