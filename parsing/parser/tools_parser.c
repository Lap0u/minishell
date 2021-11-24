#include "../../minishell.h"

void	print_args(t_simple_command *start)
{
	int i;

	i = 0;
	printf("ARGS : ");
	while (start->args[i])
	{
		printf("%s\t", start->args[i++]);
	}
	printf("\n");
}

void	print_redir(t_simple_command *start)
{
	t_redir	*save;

	save = start->redir;
	printf("REDIR : 0 = out    1 = in    2 = out_append    3 = here_doc\n");
	while (start->redir)
	{
		printf("type : %d  vers file : %s\t", start->redir->type, start->redir->file);
		start->redir = start->redir->next;
	}
	printf("\n\n");
	start->redir = save;
}

void	ft_print_sentences(t_simple_command *start)
{
	int i;

	i = 0;
	while (start)
	{
		printf("SENTENCE : %d\n\n", i++);
		printf("COMMANDE : %s\n", start->cmd);
		print_args(start);
		print_redir(start);
		start = start->next;
	}
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

char	*ft_expand_dollar(char *str, int mode, char **env)
{
	int		i;
	char	*temp;
	
	i = 0;
	if ((str[0] != '$' || mode == 8 || mode == 1) || (str[0] == '$' && !str[1]))
		return (str);
	while (env[i])
	{
		temp = ft_var_only(env[i]);
		if (ft_strcmp(temp, str + 1) == 0)
		{
			free(temp);
			free(str);
			str = ft_add_var(env[i]);
			return (str);
		}
		free(temp);
		i++;
	}
	return (NULL);

}

void	ft_free_redir(t_redir **list)
{
	t_redir *temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->file);
		free(temp);
	}
	*list = NULL;
}
