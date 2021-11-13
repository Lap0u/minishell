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

void    cd_noarg(t_simple_command *c_table)
{
    int i;

    i = 0;
    while (c_table->env[i])
    {
        if (ft_strncmp("HOME=", c_table->env[i], 5) == 0)
        {
            if (chdir(&c_table->env[i][5]) < 0)
            {
                c_table->last_ret = 1;
                perror("cd");
            }
            else
                c_table->last_ret = 0;
            return ;
        }
        i++;
    }
    fprintf(stdout, "cd: HOME not set\n");
    c_table->last_ret = 1;
}
void    ft_bi_cd(t_simple_command *c_table) //pb avec env absolu update des vars PWD OLD PWD etc voir man
{
    int ret;
    if (c_table->args_num < 1)
    {
        cd_noarg(c_table);
        return ;
    }
    ret = chdir(c_table->args[1]);
    if (ret == -1)
    {
        perror("Error");
        c_table->last_ret = 1;
    }
    else
        c_table->last_ret = 0;
}
