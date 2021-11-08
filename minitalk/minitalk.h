/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:35:38 by okushnir          #+#    #+#             */
/*   Updated: 2021/09/03 15:35:40 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>

typedef struct s_ping
{
	int	sent;
	int	reeceived;
	int	flag;
}				t_ping;

t_ping	g_pings;

void	ft_putchar(char c);
void	ft_putnbr(int nb);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	waiting(void);

#endif
