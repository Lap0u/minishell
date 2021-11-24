#include "../../minishell.h"

int 	is_expandable(char *str, int red, int quote, char **env)
{
	int		i;
	char	*temp;
	
	if (str[0] != '$' || red == RED_HERE_DOC || quote == 1)
		return (1);
	
	i = 0;
	while (env[i])
	{
		temp = ft_var_only(env[i]);
		if (ft_strcmp(temp, str + 1) == 0)
		{
			free(temp);
			return (1);
		}
		free(temp);
		i++;
	}
	return (0);
}

int	is_there_red(t_token *arr_tok, int index, int len, char **env)
{
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type == RED_HERE_DOC)
			return (0);
		else if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC && 
		arr_tok[index + 1].fl_quotes == 1)
			return (0);
		else if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC &&
		is_expandable(arr_tok[index + 1].value, 0, 0, env))
			return (0);
		index++;
	}
	return (1);
}

void	new_redir(t_token *arr_tok, t_redir **start)
{
	t_redir *save;
	t_redir	*new;
	
	save = *start;
	while (save->next)
		save = save->next;
	new = malloc(sizeof(t_redir));
	if (new == NULL)
		exit(42);///doit tout free
	new->type = arr_tok[0].type - 5;
	new->file = arr_tok[1].value;
	new->next = NULL;
	save->next = new;
}

t_redir	*ft_fill_redir(t_token *arr_tok, int index, int len, char **env)
{
	t_redir *start;
	int		bool_start;
	
	bool_start = -1;
	if (is_there_red(arr_tok, index, len, env) == 1)
		return (NULL);
	start = malloc(sizeof(t_redir));
	if (start == NULL)
		return (NULL);
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC &&
			is_expandable(arr_tok[index + 1].value, arr_tok[index].type,
			arr_tok[index + 1].fl_quotes, env))
		{
			if (bool_start == -1)
			{
				start->type = arr_tok[index].type - 5;
				if (arr_tok[index].type == RED_HERE_DOC || arr_tok[index +1].fl_quotes ==1)
					start->file = arr_tok[index + 1].value;
				else
					start->file = ft_expand_dollar(arr_tok[index + 1].value, arr_tok[index].type, env);
				start->next = NULL;
				bool_start = 0;
			}
			else
				new_redir(&arr_tok[index], &start);
			free(arr_tok[index].value);
			index++;
		}
		index++;
	}
	return (start);
}
