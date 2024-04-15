/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:11:50 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 15:30:26 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_built_in(t_shell *shell, int i)
{
	if (ft_strcmp(shell->final[i].exec[0], "pwd") == 0)
		ft_printf("%s\n", getcwd(shell->cwd, MAXPATHLEN));
	else if (ft_strcmp(shell->final[i].exec[0], "env") == 0)
		run_env(shell);
	else if (ft_strcmp(shell->final[i].exec[0], "echo") == 0)
		run_echo(shell, i);
}

int	run_builtin_no_fork(t_shell *shell, int i)
{
	int	d;

	if (ft_strcmp(shell->final[i].exec[0], "exit") == 0)
	{
		d = 0;
		if (shell->final[i].exec[1] != NULL)
		{
			d = ft_atoi(shell->final[i].exec[1]);
			free_com(shell);
			exit(d);
		}
		else
		{
			free_com(shell);
			exit(0);
		}
	}
	else if (ft_strcmp(shell->final[i].exec[0], "cd") == 0)
		return (run_cd(shell, i), 1);
	else if (ft_strcmp(shell->final[i].exec[0], "export") == 0)
		return (run_export(shell, i), 1);
	else if (ft_strcmp(shell->final[i].exec[0], "unset") == 0)
		return (run_unset(shell, i), 1);
	return (0);
}

void	handle_here_doc(t_shell *shell, int i)
{
	here_doc(shell, i);
	dup2(shell->end[1], STDOUT_FILENO);
	if (ft_strcmp(shell->final[i - 1].exec[0], "cat") == 0)
		print_here_doc(shell);
	close(STDOUT_FILENO);
	dup2(shell->fd_out, STDOUT_FILENO);
	close(0);
	dup2(shell->fd_in, STDIN_FILENO);
}

void	check_single(t_shell *shell, int i)
{
	if (access(shell->final[i].exec[0], F_OK) == 0)
	{
		if (access(shell->final[i].exec[0], X_OK) == 0)
			execve(shell->final[i].exec[0], shell->final[i].exec, shell->env);
		else
		{
			printf("%s: Permission denied\n", shell->final[i].exec[0]);
			exit(126);
		}
	}
	else
	{
		printf("%s: No such file or directory\n", shell->final[i].exec[0]);
		exit(127);
	}
}

void	run_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
}
