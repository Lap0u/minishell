/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:56:48 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/20 10:49:15 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sig_val(int ret)
{
	extern int	g_signum;

	if (g_signum != -1)
	{
		ret = g_signum;
		g_signum = -1;
	}
	return (ret);
}

void	set_signals(void)
{
	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);
}

void	set_signals2(void)
{
	signal(SIGINT, inthandler2);
	signal(SIGQUIT, quithandler2);
	signal(SIGSEGV, segvhandler2);
}
