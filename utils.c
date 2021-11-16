#include "./minishell.h"
#include "libft/libft.h"

int ft_get_args_size(char **args)
{
    int i;

    if (!args)
        return (-1);
    i = 0;
    while (args[i] != NULL)
        i++;
    return (i - 1);
}



char	*ft_var_only(char *str)
{
	int i;
	int end;
	char *res;

	i = 0;
	end = 0;
	while (str[end + 1] != '=')
		end++;
	res = malloc(sizeof(char) * end + 2);
	if (res == NULL)
		return (NULL);
	while (i <= end)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_add_var(char *str)
{
	int i;
	char *res;
	int	j;

	i = 0;
	while ((ft_strncmp(str + i, "=", 1) != 0) && str[i])
		i++;
	i += 1;
	res = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	return (res);
}

char	**ft_remove_nullvar(char **str, int i)
{
	int j;
	char **res;
	int k;

	j = 0;
	k = 0;
	while (str[j])
		j++;
	res = malloc(sizeof(char*) * j);
	if (res == NULL)
		free(str);///////toutes les chaines a free
	j = 0;
	while (str[k])
	{
		if (i != k)
			res[j++] = str[k++];
		else
			k++;
	}
	res[j] = NULL;
	free(str[i]);
	free(str);
	return (res);
}

char 	**ft_expand(char **str, int i, char **env)
{
	int j;
	char *temp;

	j = 0;
	while (env[j])
	{
		temp = ft_var_only(env[j]);
		if (ft_strncmp(temp, str[i] + 1, ft_strlen(str[i] + 1)) == 0)
		{
			free(temp);
			free(str[i]);
			str[i] = ft_add_var(env[j]);
			return (str);
		}
		free(temp);
		j++;
	}
	return (ft_remove_nullvar(str, i));
}

char	**ft_expand_var(char **str, char **env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '$')
			str = ft_expand(str, i--, env);
		else
			i++;
	}
	return (str);

}

char    **ft_get_args(char *str, char **env)
{
    int i;
    char **res;

    i = 0;
    while (str[i] && str[i] != ' ')
        i++;
    res = ft_split(str, ' ');
	if (res == NULL)
    	return (NULL);
	res = ft_expand_var(res, env);
    return (res);
}

t_redir	*ft_create_redir()
{
	t_redir *start;
	t_redir	*next;
	t_redir *last;

	start = malloc(sizeof(t_redir));
	if (start == NULL)
		return (NULL);
	start->file = ft_strdup("in1");
	start->type = 0;
	
	next = malloc(sizeof(t_redir));
	if (next == NULL)
		return (NULL);
	start->next = next;
	next->file = ft_strdup("out2");
	next->type = 1;
	
	last = malloc(sizeof(t_redir));
	if (last == NULL)
		return (NULL);
	next->next = last;
	last->file = ft_strdup("out3");
	last->type = 1;
	last->next = NULL;
	return (start);
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

void	ft_open_files (t_simple_command *c_table, t_redir *list)
{
	int i;
	
	i = 0;
	c_table->outfile = -21000;
	c_table->infile = -21000;
	while (list && c_table->outfile != -42000 && c_table->infile != -42000)
	{
		if (list->type == 1)
			ft_add_output(list->file, c_table);
		else if (list->type == 0)
			ft_add_input(list->file, c_table);
		if (c_table->outfile == -42000 || c_table->infile == -42000)
			c_table->badfd = i;
		i++;
		list = list->next;
	}
}

t_simple_command *ft_get_simple_command(char *str, char **env)
{
	t_simple_command *res;

	res = malloc(sizeof(t_simple_command));
	if (res == NULL)
		return (NULL);
	res->badfd = -1;
	res->cmd = ft_get_command(str);
    res->args = ft_get_args(str, env);
    res->args_num = ft_get_args_size(res->args);
	res->env = env;
	res->redir = ft_create_redir();
	ft_open_files(res, res->redir);
	res->last_ret = 0;
    if (res->cmd == NULL)
    {
        free(res);
        return (NULL);
    }
    return (res);
}

char	*ft_get_command(char *str)
{
	int i;
	char *res;
	
	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != ' ')
		i++;
	res = malloc (sizeof(char) * i + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		res[i] = str[i];
		i++;
	}
    res[i] = 0;
	return (res);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

