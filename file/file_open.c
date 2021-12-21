/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:38:29 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/21 15:15:32 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	ft_add_input(char *file, t_simple_command *c_table)
{
	int	ret;

	ret = open(file, O_RDONLY);
	if (ret < 0)
		return (ft_close_prev(c_table));
	if (c_table->infile != -21000)
		close(c_table->infile);
	c_table->infile = ret;
}

void	ft_add_output(char *file, t_simple_command *c_table)
{
	DIR		*folder;
	int		ret;

	folder = opendir(file);
	if (folder)
	{
		closedir(folder);
		c_table->badfd = 1;
		ft_close_prev(c_table);
		return ;
	}
	ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ret < 0)
		return (ft_close_prev(c_table));
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	c_table->outfile = ret;
}

void	ft_add_append(char *file, t_simple_command *c_table)
{
	DIR		*folder;
	int		ret;

	folder = opendir(file);
	if (folder)
	{
		closedir(folder);
		return (ft_close_prev(c_table));
	}
	ret = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ret < 0)
		return (ft_close_prev(c_table));
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	c_table->outfile = ret;
}

void	ft_add_heredoc(char *delim, t_simple_command *c_table)
{
	int		ret;
	char	*temp_name;
	char	*index;
	extern int	g_signum;
	int	stdin = dup(STDIN_FILENO);
	index = ft_itoa(c_table->pos);
	temp_name = ft_strjoin("file/.heredoc", index);
	free(index);
	ret = open(temp_name, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (ret < 0)
		return (ft_close_prev(c_table));
	write_heredoc(delim, ret, c_table->env);
	close (ret);
	ret = open(temp_name, O_RDONLY);
	free(temp_name);
	if (g_signum == 130)
	{
		dup2(stdin, STDIN_FILENO);
		write(0, "\n", 1);
	}
	if (ret < 0 || g_signum == 130)
		return (ft_close_prev(c_table));
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->infile = ret;
}

void	ft_open_files(t_simple_command *c_table, t_redir *list)
{
	t_redir	*wrong;
	extern int	g_signum;

	while (list && c_table->outfile != -42000 && c_table->infile != -42000 && g_signum != 130)
	{
		if (list->type == 0)
			ft_add_output(list->file, c_table);
		else if (list->type == 1)
			ft_add_input(list->file, c_table);
		else if (list->type == 2)
			ft_add_append(list->file, c_table);
		else if (list->type == 3)
			ft_add_heredoc(list->file, c_table);
		wrong = list;
		list = list->next;
	}
	while (list && g_signum != 130)
	{
		if (list->type == 3)
			ft_add_heredoc(list->file, c_table);
		list = list->next;
	}
	if ((c_table->outfile == -42000 || c_table->infile == -42000) && g_signum != 130)
		ft_write_wfolder(wrong, c_table);
}
