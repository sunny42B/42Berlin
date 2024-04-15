/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:41:09 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/31 13:56:37 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_expander(t_shell *shell)
{
	int	units;

	units = 0;
	ft_expander(*(shell->token), &units);
	shell->units = units;
	return (0);
}

void	redirect_parser(t_token **tmp, int *units)
{
	(*units)++;
	if ((*tmp)->type == PIPE)
		(*tmp)->type = PIPE;
	else if ((*tmp)->next != NULL)
	{
		(*tmp)->next->type = ARG;
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp)->type == HERED && (*tmp)->next != NULL)
	{
		(*tmp)->next->type = ARG;
		(*tmp) = (*tmp)->next;
	}
}

void	cmd_parser(t_token **tmp, int *units)
{
	(*units)++;
	while ((*tmp)->next != NULL && !(is_redirect((*tmp)->next->type)))
	{
		if ((*tmp)->next->type == CMD || (*tmp)->next->type == ARG)
			(*tmp)->next->type = ARG;
		(*tmp) = (*tmp)->next;
	}
}

void	arg_parser(t_token **tmp, int *units)
{
	(*tmp)->type = CMD;
	(*units)++;
	while ((*tmp)->next != NULL && !(is_redirect((*tmp)->next->type)))
	{
		if ((*tmp)->next->type == CMD || (*tmp)->next->type == ARG)
			(*tmp)->next->type = ARG;
		(*tmp) = (*tmp)->next;
	}
}

void	ft_expander(t_token *token, int *units)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == EMPTY)
			return ;
		else if (is_redirect(tmp->type))
			redirect_parser(&tmp, units);
		else if (tmp->type == CMD)
			cmd_parser(&tmp, units);
		else if (tmp->type == ARG)
			arg_parser(&tmp, units);
		else 
			printf("%s: command not found\n", tmp->name);
		tmp = tmp->next;
	}
}
