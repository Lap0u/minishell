/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/07 14:32:26 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stat_management(char *bin, int mode)
{
	if (mode / 1000 == 16 && ft_strncmp(bin, "./", 2) == 0)
	{
		write(2, "minishell: ", 12);
		write(2, bin, ft_strlen(bin));
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
	if (ft_strncmp(bin, "./", 2) == 0 && mode != 0 && mode % 33000 / 200 != 1)
	{
		write(2, "minishell: ", 12);
		write(2, bin, ft_strlen(bin));
		write(2, ": Permission denied\n", 21);
		exit(126);		
	}
	if (mode == 0 && (ft_strncmp(bin, "./", 2) == 0 || bin[0] == '/'))
	{		
		write(2, "minishell: ", 12);
		write(2, bin, ft_strlen(bin));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	if (((mode % 33000) / 200) == 0 || mode / 1000 == 16)
	{	
		write(2, "minishell: ", 12);
		write(2, bin, ft_strlen(bin));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

int	get_stat(char *str)
{
	struct stat	*buf;
	int			ret;

	buf = malloc(sizeof(struct stat));
	buf->st_mode = 0;
	if (buf == NULL)
		return (0);
	stat(str, buf);
	ret = buf->st_mode;
	free(buf);
	return (ret);
}

void	execution(t_simple_command *c_table, char **env)
{
	int	mode;

	mode = get_stat(c_table->args[0]);
	if (c_table->args[0] != 0 && (mode != 0 
	|| ft_strncmp(c_table->args[0], "./", 2) == 0 || c_table->args[0][0] == '/')) //FLAG pour fichier
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
		stat_management(c_table->args[0], mode);
		execve(c_table->args[0], c_table->args, env);
		perror("minishell : execve");
		exit(126); //126 si nom de fichier ou dossier et perror different
	}
	else
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, " : command not found\n", 22);
		exit(127);
	}
}

void	ft_bin_nofork(t_simple_command *c_table, char **env)
{
	char	**path;

	path = ft_get_paths(env);
	if (path == NULL && c_table->cmd[0] != '/')
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
	if (path == NULL && c_table->cmd[0] != '/')
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
