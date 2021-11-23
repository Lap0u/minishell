#include "../../minishell.h"

int		ft_count_args(t_token *arr_tok, int index, int len)
{
	int count;

	count = 0;
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (arr_tok[index].type == DOLLAR || arr_tok[index].type == ARG)
			count++;
		index++;
	}
	return (count);
}

int	do_var_existe(t_token **arr_tok, int len, char **env)
{
	int		i;
	int 	y;
	int 	count;
	char	*str;
	t_token *temp;
	
	count = 0;
	y = 0;
	temp = *arr_tok;
	while (y < len)
	{
		temp[y].subst = 0;
		i = 0;
		while (env[i])
		{
			str = ft_var_only(env[i]);
			if (temp[y].type == DOLLAR && ft_strncmp(str, temp[y].value + 1, ft_strlen(temp[y].value + 1)) == 0)
			{
				count++;
				temp[y].subst = 1;
			}
			else if (temp[y].type == ARG)
				count++;
			free(str);
			i++;
		}
		y++;
	}
	return (count);
}

char	**ft_fill_args(t_token *arr_tok, int index, int len, char **env)
{
	char	**args;
	int		nbr_args;
	int		i;
	(void)env;///////////

	i = 0;
	nbr_args = do_var_existe(&arr_tok, len, env);
	args = malloc(sizeof(char *) * (nbr_args + 1));
	if (args == (void *)0)
		return ((void *)0);
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (((arr_tok[index].type == DOLLAR && arr_tok[index].subst == 1) || arr_tok[index].type == ARG))
		{
			args[i] = ft_expand_dollar(arr_tok[index].value, arr_tok[index].fl_quotes, env);//expand si dollar ou args=arr.value si arg
			i++;
		}
		index++;
	}
	args[i] = (void *)0;
	return (args);
}
