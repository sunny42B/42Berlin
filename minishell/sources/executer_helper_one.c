/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:09:35 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 15:13:51 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0666);
	if (fd == -1)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		dup2(shell->fd_in, STDIN_FILENO);
		return (-1);
	}
	return (fd);
}

void	check_redir(t_shell *shell)
{
	int		i;
	char	*filename;

	i = 0;
	filename = NULL;
	while (i < shell->units)
	{
		filename = shell->final[i].exec[1];
		if (!is_redirection_valid(filename, shell, i))
			return ;
		if (shell->final[i].type == OUT)
			shell->fd[i] = open_output_file(filename);
		else if (shell->final[i].type == APP)
			shell->fd[i] = open_append_file(filename);
		else if (shell->final[i].type == IN)
			shell->fd[i] = open_input_file(filename, shell);
		i++;
	}
}

void	init_shell(t_shell *shell)
{
	shell->fd_in = dup(STDIN_FILENO);
	shell->fd_out = dup(STDOUT_FILENO);
	shell->end[0] = dup(STDIN_FILENO);
	shell->end[1] = dup(STDOUT_FILENO);
}

void	prepare_redirection(t_shell *shell)
{
	check_redir(shell);
}

int	execute_single_command(t_shell *shell, int i)
{
	handle_cmd_signals();
	if (run_builtin_no_fork(shell, i) == 1)
	{
		g_exit_status = 2;
		return (0);
	}
	else if (shell->final[i].type == APP)
	{
		append(shell, i);
		return (0);
	}
	else if (shell->final[i].type == IN)
	{
		redirect_in(shell, i);
		return (0);
	}
	else if (shell->final[i].type == OUT)
	{
		redirect_out(shell, i);
		return (0);
	}
	run_child(shell, i);
	return (0);
}
