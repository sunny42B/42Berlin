/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:50:49 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 15:16:48 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_shell *shell)
{
	int		i;
	int		len;
	t_token	*head;

	head = NULL;
	shell->token = &head;
	i = 0;
	len = ft_strlen(shell->prompt);
	while (i < len)
		fill_tokens(shell, &i, len);
	check_dollar_node(shell);
	use_set_token_type(shell, *(shell->token));
	join_when_no_spaces(shell);
	del_space_nodes(shell);
	pre_expander(shell);
	ft_parser_lstlst(shell);
	free_lexer(shell);
	return (0);
}

char	*lex_split2_cpy(int *i, char *str, int len, char chr)
{
	char	buf[100];
	int		j;

	j = 0;
	(*i)++;
	while (str[*i] != chr && *i < len)
		buf[j++] = str[(*i)++];
	buf[j] = '\0';
	(*i)++;
	return (ft_strdup(buf));
}

void	lex_split2(t_shell *shell, int *i, char chr, int len)
{
	char	*buf;
	char	*str;
	t_token	*new;

	new = NULL;
	str = shell->prompt;
	if (chr == ' ')
	{
		new = ft_token_new(ft_strdup("SPACE"), SPC);
		(*i)++;
	}
	else
	{
		buf = lex_split2_cpy(i, str, len, chr);
		if (chr == '\'')
			new = ft_token_new(buf, SQUOTE);
		else if (chr == '\"')
			new = ft_token_new(buf, DQUOTE);
		else
			printf("should not be displayed33\n");
	}
	if (!new)
		return ;
	ft_token_add_back(shell->token, new);
}

void	lex_cpy(t_shell *shell, int *i, int len)
{
	char	buf[100];
	char	*str;
	int		j;
	t_token	*new;

	j = 0;
	str = shell->prompt;
	while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"' && *i < len)
	{
		if (str[*i] == '|')
			break ;
		else
			buf[j++] = str[(*i)++];
	}
	buf[j] = '\0';
	new = ft_token_new(ft_strdup(buf), ARG);
	ft_token_add_back(shell->token, new);
}

void	lex_redirect(t_shell *shell, int *i, char c)
{
	char	buf[3];
	char	*str;
	int		j;
	t_token	*new;

	str = shell->prompt;
	j = 0;
	if (c == '|')
		buf[j] = '|';
	else if (str[*i + 1] == c)
	{
		buf[j] = c;
		buf[++j] = c;
		(*i)++;
	}
	else
		buf[j] = c;
	buf[++j] = '\0';
	(*i)++;
	new = ft_token_new(ft_strdup(buf), FLAG);
	ft_token_add_back(shell->token, new);
}
