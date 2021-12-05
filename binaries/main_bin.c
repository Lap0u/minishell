/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 14:43:32 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_simple_command *c_table, char **env)
{
	if (access(c_table->args[0], F_OK) == 0 && c_table->args[0] != 0) //FLAG pour fichier
	{
		if (c_table->outfile >= 0)
		{
			if (dup2(c_table->outfile, STDOUT_FILENO) < 0)
				perror("minishell :error");
		}
		if (c_table->infile >= 0)
		{
			if (dup2(c_table->infile, STDIN_FILENO) < 0)
				perror("minishell :error");
		}
		execve(c_table->args[0], c_table->args, env);
		perror("minishell :error execve");
		exit(127); //126 si nom de fichier ou dossier et perror different
	}
	else
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

void	ft_bin_nofork(t_simple_command *c_table, char **env)
{
	char	**path;

	path = ft_get_paths(env);
	if (path == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	ft_add_path(c_table, path);
	execution(c_table, env);
}

void	ft_exec_bin(t_simple_command *c_table, char **env)
{
	char	**path;
	pid_t	child;

	path = ft_get_paths(env);
	if (path == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": No such file or directory\n", 29);
		c_table->last_ret = 127;
		return ;
	}
	ft_add_path(c_table, path);
	if (c_table->args_num != 0)
	{
		child = fork();
		if (child < 0)
			return (perror("minishell: fork : "));
		if (child == 0)
			execution(c_table, env);
		waitpid(child, &c_table->last_ret, 0);
		c_table->last_ret = WEXITSTATUS(c_table->last_ret);
	}
	else
		c_table->last_ret = 0;
}
