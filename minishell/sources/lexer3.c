/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:39 by sung-hle          #+#    #+#             */
/*   Updated: 2023/07/31 15:04:43 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type2(t_shell *shell, t_token *token)
{
	if (token->name[0] == '\0')
		token->type = EMPTY;
	else if (ft_strcmp(token->name, "<") == 0)
		token->type = IN;
	else if (token->name[0] == '-')
		token->type = FLAG;
	else if (ft_strcmp(token->name, ">") == 0)
		token->type = OUT;
	else if (ft_strcmp(token->name, ">>") == 0)
		token->type = APP;
	else if (ft_strcmp(token->name, "<<") == 0)
		token->type = HERED;
	else if (ft_strcmp(token->name, "|") == 0)
		token->type = PIPE;
	else if (is_built_in(token->name) == 1) 
		token->type = CMD;
	else if (is_not_built_in(shell, token->name) == 1)
		token->type = CMD;
	else
		token->type = ARG;
}

void	use_set_token_type(t_shell *shell, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->quotes == SQUOTE || tmp->quotes == DQUOTE)
			tmp->type = ARG;
		else
			set_token_type2(shell, tmp);
		tmp = tmp->next;
	}
}

int	is_redirect_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	fill_tokens(t_shell *shell, int *i, int len)
{
	char	*str;

	str = shell->prompt;
	if (*i == len)
		return (1);
	while (*i < len)
	{
		if (is_redirect_char(str[*i]))
			lex_redirect(shell, i, str[*i]);
		else if (str[*i] == ' ')
			lex_split2(shell, i, ' ', len);
		else if (str[*i] == '\'')
			lex_split2(shell, i, '\'', len);
		else if (str[*i] == '\"')
			lex_split2(shell, i, '\"', len);
		else
			lex_cpy(shell, i, len);
	}
	return (0);
}

int	is_redirect(int type)
{
	return (type == 2 || type == 3 || type == 4 || type == 5 || type == 8);
}
