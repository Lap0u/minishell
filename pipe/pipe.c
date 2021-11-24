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

void	add_pos(t_simple_command *list)
{
	int i;

	i = 0;
	while (list)
	{
		list->pos = i;
		list = list->next;
		i++;
	}
}

void	close_pipes(int *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
		close(tab[i++]);
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
	add_pos(c_table);
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
		if (child < 0)
		{
			perror ("fork: ");
			return (112);
		}
		else if (child == 0)
		{
			if (c_table->pos != 0)
			{
				if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) < 0)
				{
					perror("Dup2: ");
					return (112);
				}
			}
			if (c_table->next != NULL)
			{
				if (dup2(pipefd[(i * 2) + 1], STDOUT_FILENO) < 0)
				{
					perror("Dup2: ");
					return (112);
				}
			}
			close_pipes(pipefd, nbr_pipe);
			if (ft_isbuiltin(c_table->cmd))
				ft_split_builtin(&c_table);
			else	//les builtins et exec doivent renvoyer une valeur de retour pour $?
				ft_exec_bin(c_table, c_table->env, pipefd, i);
		}
		i++;
		c_table = c_table->next;
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
	}
	close_pipes(pipefd, nbr_pipe);
	free(pipefd);
    waitpid(child, &status, 0);
    return (status);
}
