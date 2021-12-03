/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 14:27:47 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstcmd(t_simple_command *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list->pos = i;
		i++;
		list = list->next;
	}
	return (i);
}

void	close_pipes(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size * 2)
		close(tab[i++]);
}

int	ft_pipe(t_simple_command *c_table)
{
	pid_t	*childs;
	int		*pipefd;
	int		nbr_sent;
	int		status;
	int		i;

	i = 0;
	if (c_table->next == NULL)
		return (onec_exec(c_table));
	nbr_sent = ft_lstcmd(c_table);
	childs = init_childs(nbr_sent);
	pipefd = init_pipes(nbr_sent, childs);
	if (childs == NULL || pipefd == NULL)
		return (1);
	launch_exec(c_table, childs, pipefd, nbr_sent);
	close_pipes(pipefd, nbr_sent);
	free(pipefd);
	i = 0;
	while (i < nbr_sent)
		waitpid(childs[i++], &status, 0);
	free(childs);
	return (WEXITSTATUS(status));
}
