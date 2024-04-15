/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:52:09 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/01 18:18:58 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_last(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (!list)
		return (0);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_del_token(t_shell *shell, t_token *node)
{
	if (shell->token == NULL || !node)
		return ;
	if (node == *(shell->token))
		*(shell->token) = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node->name);
	free(node);
}

t_token	*ft_token_new(char *strg, int typ)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (new == NULL)
		return (0);
	else
	{
		new->name = strg;
		new->type = 0;
		new->quotes = typ;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void	ft_token_add_back(t_token **list, t_token *new)
{
	t_token	*last;

	if (*list == NULL)
		*list = new;
	else
	{
		last = ft_token_last(*list);
		last->next = new;
		new->prev = last;
	}
}

void	del_space_nodes(t_shell *shell)
{
	t_token	*token;

	token = *(shell->token);
	while (token != NULL)
	{
		while (token->next != NULL && token->next->quotes == SPC)
			ft_del_token(shell, token->next);
		token = token->next;
	}
}
