/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:24:40 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 09:32:44 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}
