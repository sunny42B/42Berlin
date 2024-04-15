/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:32 by sung-hle          #+#    #+#             */
/*   Updated: 2023/02/27 17:49:57 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
server displays seine server_pid

wartet dann auf client_pid und ft_strlen(msg)

erhaelt einen string, dessen einzelteile byteweise bestaetigt werden sollen.
int sigaction(int signum, const struct sigaction *restrict act,
                     struct sigaction *restrict oldact);

void     (*sa_sigaction)(int, siginfo_t *, void *)
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "libft/libft.h"

char	g_buffer[8 + 1];

void	sig_action(int signal, siginfo_t *info, void *blubb)
{
	int				i;
	static int		bit_count;
	unsigned char	c;

	(void) blubb;
	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		i = 7;
		if (signal == SIGUSR1)
			g_buffer[bit_count++] = '1';
		else if (signal == SIGUSR2)
			g_buffer[bit_count++] = '0';
		if (bit_count == 8)
		{
			g_buffer[bit_count] = '\0';
			c = 0;
			i = -1;
			while (++i < 8)
				c |= (g_buffer[i] - '0') << i;
			ft_putchar_fd(c, 1);
			bit_count = 0;
		}
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	(void) argc;
	(void) argv;
	ft_putnbr_fd(getpid(), 1);
	write (1, "\n", 1);
	sa.sa_sigaction = &sig_action;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
