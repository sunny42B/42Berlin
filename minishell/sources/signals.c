/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:49:49 by fhassoun          #+#    #+#             */
/*   Updated: 2023/07/28 11:00:21 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 1;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction-error QUIT\n");
		return (1);
	}
	sa.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction-error INT\n");
		return (1);
	}
	return (0);
}

void	handle_cmd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
	}
}

void	handle_sig_here(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 130;
		exit(g_exit_status);
		return ;
	}
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		return ;
	}
}
