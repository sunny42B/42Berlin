/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:41:09 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/31 15:00:15 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_q_trim(char *s)
{
	char	*p;
	int		l;

	p = s;
	l = ft_strlen(p);
}

void	double_q_trim(char *s)
{
	char	*p;
	int		l;

	p = s;
	l = ft_strlen(p);
	while (p[l - 1] == '"') 
		p[--l] = 0;
	while (*p && *p == '"')
	{
		++p;
		--l;
	}
	ft_memmove(s, p, l + 1);
}
