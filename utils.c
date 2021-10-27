#include "./minishell.h"

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

