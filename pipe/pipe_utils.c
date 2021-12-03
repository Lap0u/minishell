/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 12:56:11 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_proccessing(t_simple_command *c_table, int right[2], int left[2])
{
	int	ret;

	close(right[0]);
	close(left[1]);
	if (c_table->previous == NULL)
		close(right[1]);
	if (c_table->next == NULL)
		close(left[0]);
	if (c_table->next != NULL)
	{
		ret = dup2(left[0], STDOUT_FILENO);
		if (ret < 0)
		{
			perror("minishell: dup3");
			exit(1);
		}
	}
	if (c_table->previous != NULL)
	{
		ret = dup2(right[1], STDIN_FILENO);
		if (ret < 0)
		{
			perror("minishell: dup4");
			exit(1);
		}
	}
	if (c_table->infile == -42000 || c_table->outfile == -42000)
	{
		fprintf(stderr, "Wrong file given");
		return ;
	}
	if (ft_isbuiltin(c_table->cmd))
		ft_split_builtin(&c_table);
	else
		ft_exec_bin(c_table, c_table->env);
	close(right[1]);
	close(left[0]);
	exit(21);
}
