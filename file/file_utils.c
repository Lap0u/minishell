#include "../minishell.h"
#include "../libft/libft.h"

void	ft_file_error(t_simple_command *c_table)
{
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->infile = -42000;
	if (c_table->outfile >= 0)
		close (c_table->outfile);
	c_table->outfile = -42000;
}

int 	ft_isfolder(char *file, int ret)
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