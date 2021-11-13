/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:40 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 11:00:42 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_in_env(char *str, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
            return (1);
        else
            i++;
    }
    return (0);
}

void    ft_remove_from_env(char *str, char ***env)
{
    int i;
    char    **res;
    int j;

    i = 0;
    j = 0;
    while ((*env)[i])
        i++;
    res = malloc(sizeof(char*) * i);
    if (res == NULL)
        return (void)ft_free_3dtab((*env));
    i = 0;
    while ((*env)[j])
    {
        if (ft_strncmp(str, (*env)[j], ft_strlen(str)) != 0)
            res[i++] = (*env)[j++];
        else
            free((*env)[j++]);
    }
    res[i] = NULL;
    free(*env);
    (*env) = res;
}



void    ft_bi_unset(t_simple_command **c_table)
{
    int i;

    i = 1;
    (*c_table)->last_ret = 0;
    while ((*c_table)->args[i])
    {
        if (is_in_env((*c_table)->args[i], (*c_table)->env))
            ft_remove_from_env((*c_table)->args[i], &(*c_table)->env);
        else
            (*c_table)->last_ret++; //retour = nombre mbr non unset
        i++;
    }
    //return (0) dans tous les cas???
}