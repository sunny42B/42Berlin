/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:57:43 by fhassoun          #+#    #+#             */
/*   Updated: 2023/06/29 09:55:27 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_back(t_list **head, t_list *newnode)
{
	t_list	*node;

	node = NULL;
	if (head)
	{
		if (*head)
		{
			node = ft_lstlast(*head);
			node -> next = newnode;
		}
		else
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
	
	ft_lstadd_back(&head, ft_lstnew(test2));
	node = head;
	while (node != NULL)
	{
		printf("%s\n",(char *)node -> content);
		node = node -> next;
		
	}
	return (0);
}
*/