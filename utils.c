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

void	ft_expand(char **str, int i, char **env)
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
			return ;
		}
		free(temp);
		j++;
	}
	if (!env[j])
		str[i] = ft_strdup("");
}

void	ft_expand_var(char **str, char **env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '$')
			ft_expand(str, i, env);
		i++;
	}
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
	ft_expand_var(res, env);
    return (res);
}

t_simple_command *ft_get_simple_command(char *str, char **env)
{
	t_simple_command *res;

	res = malloc(sizeof(t_simple_command));
	if (res == NULL)
		return (NULL);
	res->cmd = ft_get_command(str);
    res->args = ft_get_args(str, env);
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

