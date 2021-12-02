/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:20 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/02 12:31:39 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bi_echo(t_simple_command *c_table)
{
	int	i;

	i = 1;
	if (ft_strcmp(c_table->args[1], "-n") == 0)
		i = 2;
	while (c_table->args[i])
	{
		write(1, c_table->args[i], ft_strlen(c_table->args[i]));
		if (c_table->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (ft_strcmp(c_table->args[1], "-n") != 0)
		write(1, "\n", 1);
	c_table->last_ret = 0;
}
