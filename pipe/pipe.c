/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 10:59:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pipe(t_simple_command *c_table)
{
    pid_t child;
    int pipe1[2];
    int pipe2[2];
    int status;
    int i;

    i = 0;
    if (c_table->next == NULL)
    {
        if (ft_isbuiltin(c_table->cmd))
            ft_split_builtin(&c_table);
        else	//les builtins et exec doivent renvoyer une valeur de retour pour $?
            ft_exec_bin(c_table, c_table->env);
        return (0);
    }
    pipe(pipe2);
    while (c_table)
    {
        if (i % 2 == 0)
            pipe(pipe1);
        else
            pipe(pipe2);
        child = fork();
        if (child < 0)
        {
            perror("Fork : ");
            return (child);
        }
        if (child == 0 && i % 2 == 0)
            ft_proccessing(c_table, pipe2, pipe1);
        else if (child == 0 && i % 2 == 1)
            ft_proccessing(c_table, pipe1, pipe2);
        i++;
        c_table = c_table->next;
    }
    waitpid(child, &status, 0);
    return (status);
}
