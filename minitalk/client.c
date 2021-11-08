/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:35:03 by okushnir          #+#    #+#             */
/*   Updated: 2021/09/03 15:35:08 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_recep(int signo, siginfo_t *info, void *uap)
{
	(void)info;
	(void)uap;
	if (signo == SIGUSR1)
	{
		g_pings.reeceived++;
		g_pings.flag = 1;
	}
}

void	usage(void)
{
	write(1, "Usage: ./client [PID] [message]\n", 32);
}

void	send_char(int pid, const char c)
{
	int	counter;

	counter = 1 << 16;
	while (counter)
	{
		if (counter & c)
		{
			if (kill(pid, SIGUSR1) == -1)
				write(1, "bad PID\n", 9);
			g_pings.sent++;
		}	
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				write(1, "bad PID\n", 9);
			g_pings.sent++;
		}
		waiting();
		usleep(50);
		counter >>= 1;
	}
}

void	main_sigusr(const char *pid_c, const char *message)
{
	int	pid;

	pid = ft_atoi(pid_c);
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	reception;
	sigset_t			set;

	ft_memset(&reception, 0, sizeof(reception));
	reception.sa_flags = SA_SIGINFO;
	reception.sa_sigaction = &send_recep;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	reception.sa_mask = set;
	sigaction(SIGUSR1, &reception, 0);
	sigaction(SIGUSR2, &reception, 0);
	g_pings.sent = 0;
	g_pings.reeceived = 0;
	g_pings.flag = 0;
	if (argc != 3)
		usage();
	else
		main_sigusr(argv[1], argv[2]);
	write(1, "The amount of signals sent : ", 29);
	ft_putnbr(g_pings.sent);
	write(1, "\nThe amount of signals received : ", 34);
	ft_putnbr(g_pings.reeceived);
	write(1, "\n", 1);
	return (0);
}
