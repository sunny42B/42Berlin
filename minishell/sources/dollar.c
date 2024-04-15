/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:59:20 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 14:46:24 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest_of_dollar(t_shell *shell, t_token **token, char *dup, char *buf)
{
	int		i;
	char	*dollar;

	i = 1;
	dup = ft_strdup((*token)->name);
	buf = ft_strchr(dup, '$');
	while (buf[i] != '\0' && (ft_isalnum(buf[i]) || buf[i] == '_'))
		i++;
	buf[i] = '\0';
	dollar = get_variable(shell, buf);
	(*token)->name = replace_substring((*token)->name, buf, dollar);
	free(dup);
}

void	check_dollar_node(t_shell *shell)
{
	t_token	*token;
	char	*buf;
	char	*dup;

	buf = NULL;
	dup = NULL;
	token = *(shell->token);
	while (token != NULL)
	{
		while (ft_strchr(token->name, '$'))
		{
			if (dollar_breaks(shell, &token))
				break ;
			else if (token->quotes != SQUOTE)
			{
				if (not_squote_qm_digit(&token, dup, buf))
					;
				else
					rest_of_dollar(shell, &token, dup, buf);
			}
		}
		token = token->next;
	}
}

char	*get_variable(t_shell *shell, char *buf)
{
	char	**env;
	char	*dollar;
	char	*str;
	int		j;

	env = shell->env;
	dollar = ft_strchr(buf, '$') + 1;
	j = 0;
	while (env[j] != NULL)
	{
		if ((ft_strncmp(env[j], dollar, ft_strlen(dollar)) == 0) \
			&& (ft_strlen(env[j]) == ft_strlen(dollar) + \
			ft_strlen(ft_strchr(env[j], '='))))
		{
			str = ft_strdup(ft_strchr(env[j], '=') + 1);
			return (str);
		}
		j++;
	}
	return (ft_strdup(""));
}

char	*replacing(char *str, const char *substr, char *replacem, char *tempb)
{
	size_t	i;
	int		j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (ft_strncmp(&str[i], substr, ft_strlen(substr)) == 0 && replacem)
		{
			k = 0;
			while (k < ft_strlen(replacem))
				tempb[j++] = replacem[k++];
			i += ft_strlen(substr) - 1;
		}
		else
			tempb[j++] = str[i];
		i++;
	}
	tempb[j] = '\0';
	free(replacem);
	free(str);
	return (tempb);
}

char	*replace_substring(char *str, const char *substr, char *replacement)
{
	int		len;
	int		slen;
	int		rlen;
	char	*temp_buffer;

	len = ft_strlen(str);
	slen = ft_strlen(substr);
	rlen = ft_strlen(replacement);
	temp_buffer = (char *)malloc((len - slen + rlen + 1) * sizeof(char));
	if (temp_buffer == NULL)
		return (ft_printf("Memory allocation failed.\n"), NULL);
	else
		return (replacing(str, substr, replacement, temp_buffer));
}
