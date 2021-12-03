/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 12:53:08 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bin_nofork(t_simple_command *c_table, char **env)
{
	char	**path;
	int		ret;

	path = ft_get_paths(env); //check access
	if (path == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	ft_add_path(c_table, path);
	if (access(c_table->args[0], X_OK) == 0 && c_table->args[0][0] != 0)
	{
		if (c_table->outfile >= 0)
		{
			ret = dup2(c_table->outfile, STDOUT_FILENO);
			if (ret < 0)
				perror("minishell: error");
		}
		if (c_table->infile >= 0)
		{
			ret = dup2(c_table->infile, STDIN_FILENO);
			if (ret < 0)
				perror("minishell :error");
		}
		execve(c_table->args[0], c_table->args, env);
		perror("minishell: execve:");
	}
	else if (c_table->args_num != 0)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	exit (0);
}

void	ft_exec_bin(t_simple_command *c_table, char **env)
{
	char	**path;
	int		ret;
	pid_t	child;

	path = ft_get_paths(env);//check access
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
		{
			if (access(c_table->args[0], X_OK) == 0 && c_table->args[0] != 0)
			{
				if (c_table->outfile >= 0)
				{
					ret = dup2(c_table->outfile, STDOUT_FILENO);
					if (ret < 0)
						perror("minishell :error");
				}
				if (c_table->infile >= 0)
				{
					ret = dup2(c_table->infile, STDIN_FILENO);
					if (ret < 0)
						perror("minishell :error");
				}
				execve(c_table->args[0], c_table->args, env);
				perror("minishell :error execve");
			}
			else
			{
				write(2, "minishell: ", 12);
				write(2, c_table->cmd, ft_strlen(c_table->cmd));
				write(2, ": command not found\n", 21);
				exit(127);
			}
		}
		waitpid(child, &c_table->last_ret, 0);
		c_table->last_ret = WEXITSTATUS(c_table->last_ret);
	}
	else
		c_table->last_ret = 0;
}
