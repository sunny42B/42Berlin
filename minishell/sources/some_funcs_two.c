/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_funcs_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:38:44 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 15:39:08 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strg_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_arr(char **arr, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				strg_swap(&(arr[j]), &(arr[j + 1]));
			j++;
		}
		i++;
	}
}

char	*remove_after_eq(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, i + 1);
	return (res);
}
