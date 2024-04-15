/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:14:48 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:53:22 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node = node -> next;
		i++;
	}
	return (i);
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
	i = 0;
	i = ft_lstsize(node);
	printf("%i\n", i);
	return (0);
}
*/