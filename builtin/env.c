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

void    ft_bi_env(t_simple_command *c_table, char **env)
{
    int i;

    i = 0;
    while (env[i])
        printf("%s\n", env[i++]);
    (void)c_table; // a modif, utiliser notre env malloc 
                    // et pas celui du main
}
