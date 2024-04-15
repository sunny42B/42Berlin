/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:30 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 16:22:52 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_digit_norminette_bitch(char **string_char, char **buf, char **qm)
{
	*buf = malloc(sizeof(char) * 3);
	ft_strlcpy(*buf, *string_char, 3);
	if ((*string_char)[1] == '0')
		*qm = ft_strdup("minishell");
	else
		*qm = ft_strdup("");
}

int	not_squote_qm_digit(t_token **token, char *dup, char *buf)
{
	char	*string_char;
	char	*qm;

	qm = NULL;
	string_char = ft_strchr((*token)->name, '$');
	if (ft_strncmp(ft_strchr((*token)->name, '$') + 1, "?", 1) == 0 || \
		ft_isdigit(string_char[1]))
	{
		dup = ft_strdup((*token)->name);
		if (ft_isdigit(string_char[1]))
			is_digit_norminette_bitch(&string_char, &buf, &qm);
		else
		{
			buf = ft_strdup("$?");
			qm = ft_itoa(g_exit_status);
		}
		(*token)->name = replace_substring((*token)->name, buf, qm);
		return (free(dup), free(buf), 1);
	}
	return (0);
}

int	dollar_breaks(t_shell *shell, t_token **token)
{
	if (ft_strlen((*token)->name) == 1 && (*token)->next != NULL && \
		(*token)->next->quotes != SPC)
	{
		ft_del_token(shell, *token);
		return (1);
	}
	else if ((ft_strlen((*token)->name) == 1 && \
		ft_strncmp((*token)->name, "$", 1) == 0) || \
		(ft_strlen(ft_strchr((*token)->name, '$')) == 1 \
		&& (*token)->name[ft_strlen((*token)->name) - 1] == '$'))
		return (1);
	else if ((*token)->quotes == SQUOTE)
		return (1);
	return (0);
}
