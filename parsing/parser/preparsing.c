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

#include "lexer.h"
#include "../../minishell.h"

int nbr_pipe(t_token *arr_tok)
{

}

int	is_there_red(t_token *arr_tok)
{

}


t_simple_command	*new_elem(t_token *arr_tok, int index)
{
	t_simple_command	*my_elem;

	my_elem = (void *)0;
	my_elem = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (my_elem != (void *)0)
	{
		my_elem->args_num = content;
		my_elem->next = (void *)0;
	}
	return (my_elem);
}

t_simple_command *creation_list_command(t_token *arr_tok)
{
	int nbr;
	t_simple_command	*lst_command;
	int	i;

	nbr = 1 + nbr_pipe(arr_tok);
	lst_command = NULL;
	lst_command = (t_simple_command *)malloc(sizeof(t_simple_command) * nbr);
	if (lst_command == (void *)0)
		return ((void *)0);
	i = 0;
	while (i < nbr)
	{
/////////
	}
}

int main(void)
{

}