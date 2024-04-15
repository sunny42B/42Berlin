/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 09:45:34 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/28 09:49:01 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test1(int fd)
{
	size_t	bytes_read;
	char	buffer[1024];

	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
}

void	del_node(t_list **node)
{
	t_list	*tmp;

	while (node && *node)
	{
		tmp = (*node)->next;
		free((*node)->content);
		free(*node);
		*node = tmp;
	}
	*node = NULL;
}
