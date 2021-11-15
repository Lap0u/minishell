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

void    cd_curpath(t_simple_command *c_table)
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

void    cd_classic(t_simple_command *c_table)
{
    char    *temp;
    int     i;
    char    **path;
    char    *complete;

    i = 0;
    while (c_table->env[i] && ft_strncmp(c_table->env[i], "CDPATH=", ft_strlen("CDPATH=")))
        i++;
    if (c_table->env[i] == NULL)
    {
        cd_curpath(c_table);
        return ;
    }
    temp = ft_strjoin("/", c_table->args[1]);
    path = ft_split(&c_table->env[i][7], ':');
    i = 0;
    while (path[i])
    {
        complete = ft_strjoin(path[i], temp);
        c_table->last_ret = chdir(complete);
        if (c_table->last_ret == 0)
        {
            printf("%s\n", complete);
            free(temp);
            free(complete);
            ft_free_3dtab(path);
            return ;
        }
        free(complete);
        i++;
    }
    cd_curpath(c_table);
}

void    ft_bi_cd(t_simple_command *c_table) //pb avec env absolu update des vars PWD OLD PWD etc voir man
{
    if (c_table->args_num > 2)
    {
        printf("cd: trop d'arguments\n");
        c_table->last_ret = 1;
    }
    else if (c_table->args_num < 1)
        cd_noarg(c_table);
    else if (c_table->args[1][0] == '/' || c_table->args[1][0] == '.')
        cd_curpath(c_table);
    else
        cd_classic(c_table);
}
