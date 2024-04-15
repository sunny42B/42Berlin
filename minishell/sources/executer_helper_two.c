/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:10:47 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 16:58:20 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_external_cmd(t_shell *shell, int i)
{
	if (ft_strcmp(shell->final[i].exec[0], "cat") == 0
		|| ft_strcmp(shell->final[i].exec[0], "yes") == 0)
		close(shell->end[0]);
	if (ft_strncmp(shell->final[i].exec[0], "./", 2) == 0)
		check_single(shell, i);
	if (try_command2(shell, i) == 2)
		execve(shell->final[i].exec[0], shell->final[i].exec, shell->env);
	else if (try_command2(shell, i) == 1)
		execve(shell->final[i].com, shell->final[i].exec, shell->env);
	else
	{
		printf("%s: command not found\n", shell->final[i].exec[0]);
		g_exit_status = 127;
		exit(127);
	}
	exit(0);
}

void	run_child(t_shell *shell, int i)
{
	shell->pid[i] = fork();
	if (shell->pid[i] == 0)
	{
		if (is_built_in(shell->final[i].exec[0]) == 1)
			run_built_in(shell, i);
		else if (shell->final[i].type == HERED)
			handle_here_doc(shell, i);
		else if (shell->final[i].type == CMD)
			handle_external_cmd(shell, i);
		else if (shell->final[i].type == APP)
			append(shell, i);
		else if (shell->final[i].type == IN)
			redirect_in(shell, i);
		else if (shell->final[i].type == OUT)
		{
			dup2(shell->end[1], STDOUT_FILENO);
			redirect_out(shell, i);
		}
		else if (shell->final[i].type == EMPTY)
			exit(0);
		else if (shell->final[i].type == PIPE)
			return ;
		exit(0);
	}
}

int	is_redirection_valid(char *filename, t_shell *shell, int i)
{
	if (shell->final[i].type == IN || shell->final[i].type == OUT
		|| shell->final[i].type == APP)
	{
		if (filename == NULL)
		{
			printf("minishell: syntax error near \
				unexpected token `newline'\n");
			g_exit_status = 2;
			return (0);
		}
	}
	return (1);
}

int	open_output_file(char *filename)
{
	return (open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666));
}

int	open_append_file(char *filename)
{
	return (open(filename, O_CREAT | O_RDWR | O_APPEND, 0666));
}
