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

char	**ft_fill_args(t_token *arr_tok, int index, int len, char **env)
{
	char	**args;
	int		nbr_args;
	int		i;
	(void)env;///////////
	i = 0;
	nbr_args = ft_count_args(arr_tok, index, len);
	args = malloc(sizeof(char *) * (nbr_args + 1));
	if (args == (void *)0)
		return ((void *)0);
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (arr_tok[index].type == DOLLAR || arr_tok[index].type == ARG)
		{
			args[i] = ft_expand_dollar(arr_tok[index].value, arr_tok[index].fl_quotes, env);//expand si dollar ou args=arr.value si arg
			i++;
		}
		index++;
	}
	args[i] = (void *)0;
	return (args);
}
