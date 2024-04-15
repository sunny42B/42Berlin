/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:19:12 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 16:19:17 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_shell *shell)
{
	t_token	**tmp;
	t_token	*next;

	tmp = shell->token;
	while (*tmp != NULL)
	{
		next = (*tmp)->next;
		free((*tmp)->name);
		free((*tmp));
		*tmp = next;
	}
}

void	join_when_no_spaces(t_shell *shell)
{
	t_token	*token;
	t_token	*tmp;
	char	*joined;

	tmp = *(shell->token);
	while (tmp != NULL)
	{
		token = *(shell->token);
		while (token != NULL)
		{
			if (token->quotes != 11 && token->next != NULL && \
			token->next->quotes != 11 && (token->type == 6 || token->type \
			== 1) && (token->next->type == 6 || token->next->type == 1))
			{
				joined = ft_strjoin(token->name, token->next->name);
				if (!joined)
					return ;
				free(token->name);
				token->name = joined;
				ft_del_token(shell, token->next);
			}
			token = token->next;
		}
		tmp = tmp->next;
	}
}
