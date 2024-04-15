/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:10:50 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 16:29:32 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_command2(t_shell *shell, int j)
{
	int	i;

	i = 0;
	if (!shell->mypaths)
		return (printf("Error in try_command2\n"), 1);
	if (access(shell->final[j].exec[0], 0) == 0)
		return (2);
	while (shell->mypaths[i] != NULL)
	{
		shell->final[j].com = ft_strjoin(shell->mypaths[i], \
			shell->final[j].exec[0]);
		if (access(shell->final[j].com, 0) == 0)
			return (1);
		free(shell->final[j].com);
		i++;
	}
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

int	is_built_in(char *str)
{
	char	**arr;
	int		i;

	i = -1;
	arr = ft_split("echo cd pwd export unset env exit", ' ');
	while (arr[++i] != NULL)
		if (ft_strcmp(str, arr[i]) == 0)
			return (ft_free(arr), 1);
	return (ft_free(arr), 0);
}

int	is_not_built_in(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (!shell->mypaths)
		return (printf("Error in is_not_built_in\n"), 1);
	if (access(str, 0) == 0)
		return (1);
	while (shell->mypaths[i] != NULL)
	{
		shell->command = ft_strjoin(shell->mypaths[i], str);
		if (!shell->command)
			return (perror("in is_not_built_in strjoin Error\n"), 1);
		if (access(shell->command, 0) == 0)
			return (free(shell->command), 1);
		free(shell->command);
		i++;
	}
	return (0);
}

void	set_token_type(t_shell *shell, t_token **token, int i)
{
	if (token[i]->name[0] == '\0')
		token[i]->type = EMPTY;
	else if (ft_strcmp(token[i]->name, "<") == 0)
		token[i]->type = IN;
	else if (token[i]->name[0] == '-')
		token[i]->type = FLAG;
	else if (ft_strcmp(token[i]->name, ">") == 0)
		token[i]->type = OUT;
	else if (ft_strcmp(token[i]->name, ">>") == 0)
		token[i]->type = APP;
	else if (ft_strcmp(token[i]->name, "<<") == 0)
		token[i]->type = HERED;
	else if (ft_strcmp(token[i]->name, "|") == 0)
		token[i]->type = PIPE;
	else if (is_built_in(token[i]->name) == 1) 
		token[i]->type = CMD;
	else if (is_not_built_in(shell, token[i]->name) == 1)
		token[i]->type = CMD;
	else
		token[i]->type = ARG;
}
