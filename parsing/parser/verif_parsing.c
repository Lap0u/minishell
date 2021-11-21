#include "../../minishell.h"

int is_redir(t_token arr_tok)
{
	if (arr_tok.type >= RED_OUT && arr_tok.type <= RED_HERE_DOC)
		return (1);
	return (0);
}

int is_text(t_token arr_tok)
{
	if (arr_tok.type == ARG  || arr_tok.type == DOLLAR)
		return (1);
	return (0);
}

int nbr_pipe(t_token *arr_tok, int len)
{
	int i;
	int count;
	
	i = 0;
	count = 1;
	if (len == 0)
		return (-1);
	if (arr_tok[0].type == PIPE)
		return (-1);
	while (i < len)
	{
		if (arr_tok[i].type == PIPE && 
		(i + 1 == len || arr_tok[i + 1].type == PIPE))
			return (-1);
		if (is_redir(arr_tok[i]) == 1 && (i + 1 == len || is_text(arr_tok[i + 1]) == 0))
			return (-1);
		if (arr_tok[i].type == PIPE)
			count++;
		i++;
	}
	return (count);
}

int skip_topipe(t_token *arr_tok, int index, int len)
{
	while (index < len)
	{
		if (arr_tok[index].type == PIPE)
			break ;
		index++;
	}
	return (index + 1);
}

int		ft_2dlen(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (-1);
	while (tab[i])
		i++;
	return (i);
}
