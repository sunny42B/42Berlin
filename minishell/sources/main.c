/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:14:25 by sung-hle          #+#    #+#             */
/*   Updated: 2023/08/02 17:03:24 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	check_args(int argc, char *argv[], char *envp[], t_shell *shell)
{
	(void)argc;
	(void)argv;
	shell->cwd = NULL;
	shell->token = NULL;
	shell->com = NULL;
	shell->command = NULL;
	handle_envp(shell, envp);
	return ;
}

void	trim(char *s)
{
	char	*p;
	int		l;

	p = s;
	l = ft_strlen(p);
	while (ft_isspace(p[l - 1]))
		p[--l] = 0;
	while (*p && ft_isspace(*p)) 
	{
		++p;
		--l;
	}
	ft_memmove(s, p, l + 1);
}

int	malloc_envp(t_shell *shell, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = 0;
	j = -1;
	len = 0;
	while (envp[i] != NULL)
		i++;
	new_env = malloc (sizeof (char *) * (i + 2));
	if (!new_env)
		return (1);
	while (envp[++j] != NULL)
	{
		len = ft_strlen(envp[j]) + 1;
		new_env[j] = malloc (sizeof(char) * len);
		if (!new_env[j])
			return (2);
		ft_strlcpy(new_env[j], envp[j], len);
	}
	new_env[j] = NULL;
	shell->env = new_env;
	return (0);
}

int	check_empty(t_shell *shell)
{
	if (!shell->prompt)
		exit (1);
	if (ft_strcmp(shell->prompt, "\"\"") == 0 \
		|| ft_strcmp(shell->prompt, "\'\'") == 0)
	{
		printf("Command '' not found\n");
		g_exit_status = 127;
		return (1);
	}
	else if (ft_strcmp(shell->prompt, "") == 0 || ft_strisspace(shell->prompt))
		return (1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = (t_shell *) malloc (sizeof(t_shell));
	if (!shell)
		return (1);
	memset (shell, '\0', sizeof(*shell));
	check_args(argc, argv, envp, shell);
	if (malloc_envp(shell, envp))
		return (1);
	while (1)
	{
		signals();
		shell->prompt = readline("minishell> ");
		if (check_empty(shell) == 1)
			continue ;
		add_history(shell->prompt);
		trim(shell->prompt);
		lexer(shell);
		if (executer(shell) != 0)
			break ;
		free_com(shell);
	}
	rl_clear_history();
	clean_up(shell);
	return (0);
}
