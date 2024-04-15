/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 06:29:52 by fhassoun          #+#    #+#             */
/*   Updated: 2022/12/08 11:52:43 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_front(t_list **head, t_list *newnode)
{
	if (head)
	{
		if (*head)
			newnode -> next = *head;
		*head = newnode;
	}
}
/*
int		main(void)
{
	t_list	*node;
	t_list	*head;
	char	*test1;
	char	*test2;

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
	return (0);
}
*/
