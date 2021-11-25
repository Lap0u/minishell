/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/25 14:01:12 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	ft_split_builtin(t_simple_command **c_table)
{
	int	ret;
	int	stdout;

	stdout = dup(STDOUT_FILENO);
	if ((*c_table)->outfile >= 0)
	{
		ret = dup2((*c_table)->outfile, STDOUT_FILENO);
		if (ret < 0)
			perror("Error");
	}
	if (ft_strcmp((*c_table)->cmd, "echo") == 0)
		ft_bi_echo(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "cd") == 0)
		ft_bi_cd(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "pwd") == 0)
		ft_bi_pwd(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "export") == 0)
		ft_bi_export(c_table);
	else if (ft_strcmp((*c_table)->cmd, "unset") == 0)
		ft_bi_unset(c_table);
	else if (ft_strcmp((*c_table)->cmd, "env") == 0)
		ft_bi_env(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "exit") == 0)
		ft_bi_exit(*c_table);
	ret = dup2(stdout, STDOUT_FILENO);
	if (ret < 0)
		perror("Error");
}
