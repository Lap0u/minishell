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

void    print_expformat(const char *str)
{
    int i;

    i = 0;
    write(1, "export ", ft_strlen("export "));
    while (str[i] && str[i] != '=')
        write(1, &str[i++], 1);
    if (str[i] != 0)
    {
        write(1, &str[i++], 1);
        write(1, "\"", 1);
        while (str[i])
            write(1, &str[i++], 1);
        write(1, "\"", 1);
    }
    write(1, "\n", 1);
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
        print_expformat(sorted[i]);
        free(sorted[i++]);
    }
    free(sorted);
}

int     is_valid_export(char *str)
{
    int i;

    i = 0;
    if ((ft_isalpha(str[i]) == 0 && str[i] != '_') || (str[i] == '_' && str[i + 1] == 0))
        return (1);
    while (str[i]  && str[i] != '=')
    {
        if (ft_isalnum(str[i]) == 0 && str[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

void    ft_export_replace(char *str, char *full, t_simple_command **c_table, int i)///check comportement avec export ex et ex= et ex=1
{
    if (str[0] == 0)///arg seul
        return ;
    else if (str[0] == '=' && str[1] == 0)//arg= + rien
    {
        free((*c_table)->env[i]);
        (*c_table)->env[i] = ft_strdup(full);
    }
    else if (str[0] == '=' && str[1])//arg=xxx
    {
        free((*c_table)->env[i]);
        (*c_table)->env[i] = ft_strdup(full);
    }
    if ((*c_table)->env[i] != NULL)
        (*c_table)->last_ret = 0;
    else///a check
    {
        perror("Malloc");
        (*c_table)->last_ret = 1;
        ft_proper_free(*c_table);
    }
    
}

void    ft_export_addone(char *str, char *full, t_simple_command **c_table)////check comportement avec export ex et ex= et ex=1
{
    int i;
    char **tab;

    i = 0;
    (void)str;
    while ((*c_table)->env[i])
        i++;
    tab = malloc(sizeof(char *) * (i + 2));
    if (tab == NULL)
    {
        (*c_table)->last_ret = 1;
        return ;
    }
    i = 0;
    while ((*c_table)->env[i])
    {
        tab[i] = (*c_table)->env[i];
        i++;
    }
    tab[i] = ft_strdup(full);
    tab[i + 1] = NULL;
    free((*c_table)->env);
    (*c_table)->env = tab;
    (*c_table)->last_ret = 0;////checker les malloc foireux
}

void    ft_export_add(char *toadd, t_simple_command **c_table)
{
    int i;
    int len;

    len = 0;
    i = 1;
    while ((*c_table)->env[i])
    {
        len = 0;
        while ((*c_table)->env[i][len] != '=' && (*c_table)->env[i][len])
            len++;
        if (ft_strncmp(toadd, (*c_table)->env[i], len) == 0)
        {
            ft_export_replace(&toadd[len], toadd, c_table, i);
            return ;
        }
        i++;
    }
    len = 0;
    while (toadd[len] != '=' && toadd[len])
        len++;
    ft_export_addone(&toadd[len], toadd, c_table);
}

void    ft_export_arg(t_simple_command **c_table)
{
    int i;

    i = 1;
    while ((*c_table)->args[i] != NULL)
    {
        if (is_valid_export((*c_table)->args[i]) == 0)
            ft_export_add((*c_table)->args[i], c_table);
        i++;
    }
}

void    ft_bi_export(t_simple_command **c_table)
{
    if ((*c_table)->args_num == 0)
        ft_export_noarg(*c_table);
    else
        ft_export_arg(c_table);
}