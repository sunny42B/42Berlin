/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:26:45 by fhassoun          #+#    #+#             */
/*   Updated: 2023/01/02 08:53:10 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
int		var_find(const char var, va_list lst);
int		print_char(char c);
int		print_str(char *str);
int		print_perc(char c);
int		print_nbr(int n);
int		print_hex(unsigned int value, char var);
int		print_ptr(unsigned long long value, char var);
int		print_ull(unsigned int value, char var);
char	*ft_swap(char *buf, int i, char var);

#endif