/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 07:00:47 by fhassoun          #+#    #+#             */
/*   Updated: 2023/03/18 07:09:28 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static int	trim_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static int	trim_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = trim_start(s1, set);
	end = trim_end(s1, set);
	len = end - start;
	if (len < 0)
		len = 0;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + start, len);
	return (res);
}

// int	main(void)
// {
// 	char const *s1 = "  \t \t \n  1 \n\n\n\t";
// 	char const *set = " \n\t";
// 	char	*buf;

// 	buf = ft_strtrim(s1, set);
// 	ft_putendl_fd(buf, 1);
// 	free(buf);
// 	return (0);
// }