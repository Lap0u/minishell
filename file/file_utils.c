/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:42:23 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/08 11:20:15 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	ft_write_wfolder(char *str, int i)
{
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	if (i == 1)
		write(2, "Is a folder\n", 13);
	else
		perror(NULL);
}

void	ft_file_error(t_simple_command *c_table)
{
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->infile = -42000;
	if (c_table->outfile >= 0)
		close (c_table->outfile);
	c_table->outfile = -42000;
}

int	ft_isfolder(char *file, int ret)
{
	int		bytes;
	char	buff[10];

	bytes = read(ret, buff, 1);
	close (ret);
	if (bytes < 0)
		return (0);
	bytes = open(file, O_RDONLY);
	if (bytes < 0)
		return (0);
	return (1);
}

void	ft_close_prev(t_simple_command *c_table)
{
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->outfile = -42000;
	c_table->infile = -42000;
}

void	write_heredoc(char *delim, int ret)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			write(2, "minishell: warning: \"heredoc\"", 30);
			write(2, "closed by EOF (instead of \" ", 29);
			write(2, delim, ft_strlen(delim));
			write(2, " \")\n", 5);
			return ;
		}
		if (strcmp(str, delim) == 0)
		{
			free(str);
			return ;
		}
		write(ret, str, ft_strlen(str));
		write(ret, "\n", 1);
		free(str);
	}
}
