/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:29:49 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/28 10:37:58 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	while (*envp != NULL && ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	handle_envp(t_shell *shell, char *envp[])
{
	int		i;
	char	*path;

	path = find_path(envp);
	shell->mypaths = ft_split(path, ':');
	i = -1;
	while (shell->mypaths[++i] != NULL)
	{
		shell->mypaths[i] = ft_gnl_strjoin(shell->mypaths[i], "/");
	}
}

char	*find_path2(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			path = &envp[i][5];
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	get_new_env(t_shell *shell)
{
	int		i;
	char	*path;

	path = find_path2(shell->env);
	if (!path)
	{
		free(shell->mypaths);
		shell->mypaths = NULL;
		shell->mypaths = malloc(sizeof(char *) * 2);
		shell->mypaths[0] = "/";
		shell->mypaths[1] = "\0";
		return ;
	}
	shell->mypaths = ft_split(path, ':');
	i = -1;
	while (shell->mypaths[++i] != NULL)
	{
		shell->mypaths[i] = ft_gnl_strjoin(shell->mypaths[i], "/");
	}
}

void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->mypaths[i])
	{
		ft_printf("%s\n", shell->mypaths[i]);
		i++;
	}
}
