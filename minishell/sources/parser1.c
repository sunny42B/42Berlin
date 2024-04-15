/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:07:08 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 15:36:54 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_for_parser_cmd(t_token **token)
{
	int		i;
	t_token	*tmp;

	tmp = *token;
	i = 0;
	while (tmp != NULL && (!is_redirect(tmp->type)))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**parser_cmd(t_shell *shell, t_token **token)
{
	char	**ex;
	int		i;
	int		j;

	(void)shell;
	i = len_for_parser_cmd(token);
	ex = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ex)
		return (perror("Fehler in parser_cmd\n"), NULL);
	j = 0;
	while (j < i - 1)
	{
		ex[j++] = ft_strdup((*token)->name);
		*token = (*token)->next;
	}
	ex[j] = ft_strdup((*token)->name);
	ex[++j] = NULL;
	return (ex);
}

char	**parser_redirect_else(t_token **token, char **ex)
{
	ex = (char **)malloc(sizeof(char *) * 3);
	if (!ex)
		return (perror("Fehler in parser_redirect\n"), NULL);
	ex[0] = ft_strdup((*token)->name);
	if (!ex[0])
		return (NULL);
	if ((*token)->next != NULL)
	{
		(*token) = (*token)->next;
		ex[1] = ft_strdup((*token)->name);
		if (!ex[1])
			return (NULL);
		ex[2] = NULL;
	}
	return (ex);
}

char	**parser_redirect(t_shell *shell, t_token **token)
{
	char	**ex;

	(void)shell;
	ex = NULL;
	if ((*token)->type == PIPE)
	{
		ex = (char **)malloc(sizeof(char *) * 2);
		if (!ex)
			return (perror("Fehler in parser_redirect\n"), NULL);
		ex[0] = ft_strdup("|");
		if (!ex[0])
			return (NULL);
		ex[1] = NULL;
	}
	else
		ex = parser_redirect_else(token, ex);
	return (ex);
}
