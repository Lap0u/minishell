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

// void    ft_free_redir(t_redir *list)
// {
//     t_redir *temp;

//     while (list)
//     {
//         temp = list;
//         list = list->next;
//         free(temp->file);
//         free(temp);
//         temp = NULL;
//     }
// }

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
    else if (c_table->env)
         ft_free_2dstr(c_table->env);
    if (c_table->args)
        ft_free_2dstr(c_table->args);
    if (c_table->redir)
        ft_free_redir(c_table->redir);
    if (c_table->infile >= 0)
        close(c_table->infile);
    if (c_table->outfile >= 0)
        close(c_table->outfile);
    free(c_table);
    return (0);
}