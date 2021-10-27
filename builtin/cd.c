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

void    ft_bi_cd(t_simple_command *c_table)
{
    int ret;
    ret = chdir(c_table->args[1]);
    if (ret == -1)
        perror("Error");
    free(c_table);
}
