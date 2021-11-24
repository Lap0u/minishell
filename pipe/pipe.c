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

int	ft_lstcmd(t_simple_command *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int		ft_pipe(t_simple_command *c_table)
{
    pid_t child;
	int	*pipefd;
    int nbr_pipe;
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
    nbr_pipe = ft_lstcmd(c_table);
	pipefd = malloc(sizeof(int) * nbr_pipe);
	if (pipefd == NULL)
	{
		perror("Malloc:");
		return (112);
	}
	while (i < nbr_pipe)
	{
		if (pipe(pipefd + i * 2) < 0)
		{
			perror("Pipe:");
			return (112);
		}
		i++;
	}
	i = 0;
    while (c_table)
    {
        child = fork();
        // if (child < 0)
        // {
        //     perror("Fork : ");
        //     return (child);
        // }
        // if (child == 0 && i % 2 == 0)
        //     ft_proccessing(c_table, pipe2, pipe1);
        // else if (child == 0 && i % 2 == 1)
        //     ft_proccessing(c_table, pipe1, pipe2);
        // i++;
        c_table = c_table->next;
    }
    waitpid(child, &status, 0);
    return (status);
}
