/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 11:00:36 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_cp_env(char **sorted, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        sorted[i] = ft_strdup(env[i]);
        i++;
    }
    sorted[i] = 0;
}

void    ft_sort_sorted(char **tab)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (tab[i])
    {
        j = i + 1;
        while (tab[j])
        {
            if (ft_strcmp(tab[i], tab[j]) > 0)
            {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void    ft_export_noarg(t_simple_command *c_table)
{
    int     i;
    char    **sorted;
    
    i = 0;
    while (c_table->env[i])
        i++;
    sorted = malloc(sizeof(char*) * (i + 1));
    if (sorted == NULL)
        return; //null;
    ft_cp_env(sorted, c_table->env);
    ft_sort_sorted(sorted); //add quote apres egal??
    i = 0;
    while (sorted[i])
    {
        printf("declare -x %s\n", sorted[i]);
        free(sorted[i++]);
    }
    free(sorted);
}

void    ft_bi_export(t_simple_command *c_table)
{
    if (c_table->args_num == 0)
        ft_export_noarg(c_table);
    //else
      //  ft_export_arg(c_table, env);
}
