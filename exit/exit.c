/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 10:59:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void    ft_free_2dstr(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

int ft_proper_free(t_simple_command *c_table)
{
    if (c_table == NULL)
        return (0);
    if (c_table->cmd)
        free(c_table->cmd);
    if (c_table->args)
        ft_free_2dstr(c_table->args);
    if (c_table->env)
        ft_free_2dstr(c_table->env);
    free(c_table);
    return (0);
}