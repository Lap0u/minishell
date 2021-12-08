/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:34:52 by okushnir          #+#    #+#             */
/*   Updated: 2021/09/03 15:34:55 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	display_pid(void)
{
	pid_t	id_serv;

	id_serv = getpid();
	write(1, "PID = ", 6);
	ft_putnbr(id_serv);
	write(1, "\n", 1);
}

void	handle_sigusr(int signo, siginfo_t *info, void *uap)
{
	static char	c = 0;
	static int	counter = 1 << 16;

	(void)info;
	(void)uap;
	if (signo == SIGUSR1)
	{
		c |= counter;
		counter >>= 1;
		printf("info->si_pid = %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		counter >>= 1;
		printf("info->si_pid = %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
	}
	if (counter == 0)
	{
		write(1, &c, 1);
		counter = 1 << 16;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			set;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sa.sa_mask = set;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	display_pid();
	while (1)
		pause();
	return (0);
}
