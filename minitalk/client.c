/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:26 by sung-hle          #+#    #+#             */
/*   Updated: 2023/02/27 18:23:55 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
wir sehen die server_pid und starten dann den client mit den argumenten
server_pid und dem zu sendenden string

der string soll gesendet werden mit vorangehendem ft_strlen fuer die client_pid
 - separat oder inklusive dem fuer den string

byteweise soll auf eine bestaetigung gewartet werden bevor weiter verschickt wird

*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "libft/libft.h"

static volatile sig_atomic_t	g_confirmation_received = 0;

void	confirmation_handler(int sig)
{
	(void)sig;
	g_confirmation_received = 1;
}

int	confirmation(int *sa_return)
{
	while (!g_confirmation_received)
	{
		if (sa_return == 0)
			return (g_confirmation_received = 1);
		if (usleep(10000) == 0)
			error("Error, no confirmation received");
	}
	return (1);
}

void	send_char(int pid, unsigned char ch)
{
	int					bit;
	int					signal;
	struct sigaction	sa;
	int					sa_return;

	sa.sa_handler = confirmation_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	bit = 0;
	while (bit < 8)
	{
		if ((ch >> bit++) & 1)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		if (kill(pid, signal) < 0)
			error("ERROR sending signal");
		sa_return = sigaction(SIGUSR1, &sa, NULL);
		if (sa_return == -1)
			error("ERROR setting up confirmation handler");
		while (!confirmation(&sa_return))
			usleep(10000);
		g_confirmation_received = 0;
	}
}

void	send_string(int pid, char *str)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (str[i] != '\0')
	{
		c = str[i++];
		send_char(pid, c);
	}
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*message;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", 1);
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	send_string(server_pid, message);
	return (0);
}
