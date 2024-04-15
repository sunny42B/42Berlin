/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:34:21 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 17:03:34 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipeline_two(t_shell *shell, int *i, int *prev_fd)
{
	pipe(shell->end);
	if (*i > 0)
		dup2(*prev_fd, STDIN_FILENO);
	dup2(shell->end[1], STDOUT_FILENO);
	handle_cmd_signals();
	run_child(shell, *i);
	close(shell->end[1]);
	close(STDIN_FILENO);
	if (*prev_fd != -1)
		close(*prev_fd);
	dup2(shell->end[0], STDIN_FILENO);
	*prev_fd = shell->end[0];
	(*i)++;
}

void	handle_pipeline(t_shell *shell, int *i, int *prev_fd)
{
	if (ft_strcmp(shell->final[*i].exec[0], "|") == 0)
	{
		(*i)++;
		return ;
	}
	if (ft_strcmp(shell->final[*i].exec[0], ">") == 0
		&& ft_strcmp(shell->final[*i + 1].exec[0], ">") == 0)
	{
		(*i)++;
		return ;
	}
	if (ft_strcmp(shell->final[*i].exec[0], ">>") == 0
		&& ft_strcmp(shell->final[*i + 1].exec[0], ">>") == 0)
	{
		(*i)++;
		return ;
	}
	if (ft_strcmp(shell->final[*i].exec[0], "cat") == 0
		&& ft_strcmp(shell->final[*i + 1].exec[0], "<<") == 0)
	{
		(*i)++;
		return ;
	}
	handle_pipeline_two(shell, i, prev_fd);
}

void	execute_multiple_commands(t_shell *shell)
{
	int	i;
	int	prev_fd;

	i = 0;
	prev_fd = -1;
	while (i < shell->units - 1)
	{
		handle_pipeline(shell, &i, &prev_fd);
	}
	dup2(shell->fd_out, STDOUT_FILENO);
	run_child(shell, i);
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->end[0]);
	close(shell->end[1]);
	if (shell->units > 1 && prev_fd > 0)
		close(prev_fd);
}

void	wait_and_cleanup(t_shell *shell)
{
	int	i;
	int	status;

	i = shell->units;
	while (i >= 0)
	{
		if (shell->pid[i] > 0)
		{
			waitpid(shell->pid[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
		if (shell->fd[i] > 0)
			close(shell->fd[i]);
		i--;
	}
	close(shell->fd_in);
	close(shell->fd_out);
	free_executer(shell);
}

int	executer(t_shell *shell)
{
	init_shell(shell);
	prepare_redirection(shell);
	if (shell->units == 1)
		execute_single_command(shell, 0);
	else if (shell->units != 0)
	{
		execute_multiple_commands(shell);
	}
	wait_and_cleanup(shell);
	return (0);
}
