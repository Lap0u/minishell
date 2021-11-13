/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:25 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 11:00:26 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_bi_cd(t_simple_command *c_table) //pb avec env absolu et sans arg //update des vars PWD OLD PWD etc voir man
{
    int ret;
    ret = chdir(c_table->args[1]);
    if (ret == -1)
    {
        perror("Error");
        c_table->last_ret = 1;
    }
    else
        c_table->last_ret = 0;
}
