/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 11:00:48 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_bi_env(t_simple_command *c_table)
{
    int i;

    i = 0;
    while(c_table->env[i])
    {
        write(1, c_table->env[i], ft_strlen(c_table->env[i]));
        write(1, "\n", 1);
        i++;
    }
    c_table->last_ret = 0;
}
