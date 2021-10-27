#include "minishell.h"

int ft_get_args_size(char **args)
{
    int i;

    if (!args)
        return (-1);
    i = 0;
    while (args[i] != NULL)
        i++;
    return (i);
}
char    **ft_get_args(char *str)
{
    int i;
    char **res;

    i = 0;
    while (str[i] && str[i] != ' ')
        i++;
    res = ft_split(str, ' ');
    if (res == NULL)
        return (NULL);
    return (res);
}

t_simple_command *ft_get_simple_command(char *str)
{
	t_simple_command *res;

	res = malloc(sizeof(t_simple_command));
	if (res == NULL)
		return (NULL);
	res->cmd = ft_get_command(str);
    res->args = ft_get_args(str);
    res->args_num = ft_get_args_size(res->args);
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
    if (!str)
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
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

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
/*
void	ft_split_builtin(t_simple_command *c_table)
{
	if (ft_strcmp(str, "echo") == 0)
		ft_bi_echo(c_table);
	else if (ft_strcmp(str, "cd") == 0)
		ft_bi_cd(c_table);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_bi_pwd(c_table);
	else if (ft_strcmp(str, "export") == 0)
		ft_bi_export(c_table);
	else if (ft_strcmp(str, "unset") == 0)
		ft_bi_unset(c_table);
	else if (ft_strcmp(str, "env") == 0)
		ft_bi_env(c_table);
	else if (ft_strcmp(str, "exit") == 0)
		ft_bi_exit(c_table);
}*/