/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:24:10 by okushnir          #+#    #+#             */
/*   Updated: 2021/05/20 13:24:12 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "../../minishell.h"

int is_redir(t_token arr_tok)
{
	if (arr_tok.type >= RED_OUT && arr_tok.type <= RED_HERE_DOC)
		return (0);
	return (1);
}

int is_text(t_token arr_tok)
{
	if ((arr_tok.type <= ARG && arr_tok.type >= COMMANDE) || arr_tok.type == DOLLAR)
		return (0);
	return (1);
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
		if (is_redir(arr_tok[i]) == 0 && (i + 1 == len || is_text(arr_tok[i + 1]) != 0))
			return (-1);
		if (arr_tok[i].type == PIPE)
			count++;
		i++;
	}
	return (count);
}

int	is_there_red(t_token *arr_tok)
{
	(void)arr_tok;
	return (0);
}


t_simple_command	*new_elem(t_token *arr_tok, int index)
{
	t_simple_command	*my_elem;

	my_elem = (void *)0;
	my_elem = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (my_elem != (void *)0)
	{
		// my_elem->args_num = content; ////
		my_elem->next = (void *)0;
	}
	(void)arr_tok;///////
	(void)index;//////
	return (my_elem);
}

t_simple_command *creation_list_command(t_token *arr_tok, int arr_len)
{
	int nbr;
	t_simple_command	*lst_command;
	int	i;

	nbr = nbr_pipe(arr_tok, arr_len);
	if (nbr < 0)
		return ((void *)0);
	lst_command = NULL;
	lst_command = (t_simple_command *)malloc(sizeof(t_simple_command) * nbr);
	if (lst_command == (void *)0)
		return ((void *)0);
	i = 0;
	while (i < nbr)
	{
		i++;////
	}
	return (lst_command);////
}

int main(void)
{
	t_token	*arr;
	int		len;
	int		i;
	int		pipes;
	char test[] = "<> $$ | echo\' | < ls -\"\'la \"plop  <|<";

	printf("text: %s\n", test);
	printf("strlen: %ld\n", ft_strlen(test));

	len = nbr_words(test);
	printf("nbr_words: %d\n\n", len);

	i = 0;
	arr = ft_split_tokens(test);// semble ok sauf " " ??
	typification(arr, len);//semble ok
	pipes = nbr_pipe(arr, len);
	while (i < len)
	{
		printf("\nvalue: %s\n", arr[i].value);
		printf("type: %d\n", arr[i].type);
		printf("fl_quotes: %d\n", arr[i].fl_quotes);
		free(arr[i].value);
		// free(arr[i]);
		i++;
	}
	printf("\nnbr_pipe: %d", pipes);
	free(arr);
	return (0);
}