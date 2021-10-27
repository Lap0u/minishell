/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:29 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 11:00:31 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_bi_pwd(t_simple_command *c_table)
{
    char wd[PATH_MAX];

    if (!getcwd(wd, PATH_MAX))
        perror("Error");
    else
        printf("%s\n", wd);
    free(c_table); //incomplet
}
