/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:22:27 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 16:32:59 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_lstlst_cmd(t_shell *shell, t_token **token, int *j)
{
	shell->final[(*j)].type = (*token)->type;
	shell->final[(*j)].exec = parser_cmd(shell, token);
	if (shell->final[(*j)].exec == NULL)
		return (ft_printf("Fehler bei lstlst_cmd[%d]\n", j), -2);
	(*j)++;
	return (0);
}

int	parser_lstlst_redirect(t_shell *shell, t_token **token, int *j)
{
	shell->final[(*j)].type = (*token)->type;
	shell->final[(*j)].exec = parser_redirect(shell, token);
	if (shell->final[(*j)].exec == NULL)
		return (printf("Fehler bei lstlst_redirect[%d]\n", (*j)), -2);
	(*j)++;
	return (0);
}

int	ft_parser_lstlst(t_shell *shell)
{
	int		j;
	t_token	*token;

	shell->final = (t_exe *) malloc(sizeof(t_exe) * (shell->units));
	token = *(shell->token);
	j = 0;
	while (token != NULL || j < shell->units)
	{
		if (token->type == EMPTY)
			break ;
		if (token->type == CMD)
			parser_lstlst_cmd(shell, &token, &j);
		else if (is_redirect(token->type))
			parser_lstlst_redirect(shell, &token, &j);
		if (token == NULL)
			break ;
		else
			token = token->next;
	}
	return (0);
}
