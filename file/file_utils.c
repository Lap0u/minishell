/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:42:23 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/01 12:48:00 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	ft_write_wfolder(char *str, int i)
{
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	if (i == 0)
		write(2, ": Is a directory\n", 18);
	else if (i == 1)
		write(2, ": Permission denied\n", 21);
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
