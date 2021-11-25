#include "../minishell.h"
#include "../libft/libft.h"

void	ft_add_input(char *file, t_simple_command *c_table)
{
	int ret;

	ret = open(file, O_RDONLY);
	if (ret < 0)
	{
		ft_close_prev(c_table);
		return ;
	}
	if (c_table->infile != -21000)
		close(c_table->infile);
	c_table->infile = ret;
}

void	ft_add_output(char *file, t_simple_command *c_table) //ajouter selon > ou >>
{
	DIR* folder;
	int ret;

	folder = opendir(file);
	if (folder)
	{
		closedir(folder);
		ft_close_prev(c_table);
		return ;
	}
	ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (ret < 0)
	{
		ft_close_prev(c_table);
		return ;
	}	
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	c_table->outfile = ret;
}

void	ft_add_append(char *file, t_simple_command *c_table)
{
		DIR* folder;
	int ret;

	folder = opendir(file);
	if (folder)
	{
		closedir(folder);
		ft_close_prev(c_table);
		return ;
	}
	ret = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if (ret < 0)
	{
		ft_close_prev(c_table);
		return ;
	}	
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	c_table->outfile = ret;
}

void	ft_add_heredoc(char *delim, t_simple_command *c_table)
{
	int	ret;
	char *str;

	ret = open("file/.heredoc",  O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (ret < 0)
	{
		ft_close_prev(c_table);
		return ;
	}
	while (1)/////voir quoi faire avec ctrl+D
	{
		str = readline("> ");
		if (strcmp(str, delim) == 0)
		{
			free(str);
			break ;
		}
		write(ret, str, ft_strlen(str));
		write(ret, "\n", 1);
		free(str);
	}
	if (c_table->infile >= 0)
		close(c_table->infile);
	close (ret);
	ret = open("file/.heredoc", O_RDONLY);
	if (ret < 0)
	{
		ft_close_prev(c_table);
		return ;
	}
	c_table->infile = ret;
}

void	ft_open_files (t_simple_command *c_table, t_redir *list)
{
	int i;
	
	i = 0;
	c_table->outfile = -21000;
	c_table->infile = -21000;
	while (list && c_table->outfile != -42000 && c_table->infile != -42000)
	{
		if (list->type == 0)
			ft_add_output(list->file, c_table);
		else if (list->type == 1)
			ft_add_input(list->file, c_table);
		else if (list->type == 2)
			ft_add_append(list->file, c_table);
		else if (list->type == 3)
			ft_add_heredoc(list->file, c_table);
		if (c_table->outfile == -42000 || c_table->infile == -42000)
			c_table->badfd = i;
		i++;
		list = list->next;
	}
}