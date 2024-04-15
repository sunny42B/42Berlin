/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:26:13 by fhassoun          #+#    #+#             */
/*   Updated: 2023/06/29 09:57:15 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstlast(t_list *node)
{
	while (node != NULL)
	{
		if (!node -> next)
			return (node);
		node = node -> next;
	}
	return (node);
}
/*
int	main(void)
{
	t_list	*node;
	t_list	*head;
	char	*test1;
	char	*test2;
	int	i;

	test1 = "teststring";
	test2 = "anotherstring";
	head = ft_lstnew(test1);
	//printf("%s\n",(char *)head -> content);
	ft_lstadd_front(&head, ft_lstnew(test2));
	node = head;
	while (node != NULL)
	{
		printf("%s\n",(char *)node -> content);
		node = node -> next;
		
	}
	node = head;
	node = ft_lstlast(node);
	printf("%s\n",(char *)node -> content);
	return (0);
}
*/