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
#include "../../minishell.h"

t_simple_command	*new_elem(t_token *arr_tok, int index, int len)
{
	t_simple_command	*my_elem;

	my_elem = (void *)0;
	my_elem = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (my_elem != (void *)0)
	{
		my_elem->args = ft_fill_args(arr_tok, index, len);
		my_elem->cmd = my_elem->args[0];
		my_elem->redir = ft_fill_redir(arr_tok, index, len);
		ft_open_files(my_elem, my_elem->redir); // a voir!!!
		my_elem->args_num = ft_2dlen(my_elem->args); ////
		my_elem->next = (void *)0;
	}
	return (my_elem);
}

void	add_new_elem(t_simple_command **st, t_token *arr_tok, int ind, int len)
{
	t_simple_command *save;

	save = *st;
	while (save->next)
		save = save->next;
	save->next = new_elem(arr_tok, ind, len);
}

void	add_env_in_elem(t_simple_command *lst_command, char **env)
{
	t_simple_command	*temp;

	temp = lst_command;
	while (temp)
	{
		temp->env = env;
		temp = temp->next;
	}
}

t_simple_command *creation_list_command(t_token *arr_tok, int arr_len, char **env)
{
	int nbr_elem;
	t_simple_command	*lst_command;
	int	i;
	int index;

	index = 0;
	nbr_elem = nbr_pipe(arr_tok, arr_len);
	if (nbr_elem < 0)
		return ((void *)0);
	lst_command = NULL;
	lst_command = new_elem(arr_tok, index, arr_len);
	index = skip_topipe(arr_tok, index, arr_len);
	if (lst_command == (void *)0)
		return ((void *)0);
	i = 1;
	while (i < nbr_elem)
	{
		add_new_elem(&lst_command, arr_tok, index, arr_len);
		index = skip_topipe(arr_tok, index, arr_len);
		i++;
	}
	add_env_in_elem(lst_command, env);
	return (lst_command);////
}

// int main(void)
// {
// 	t_token	*arr;
// 	int		len;
// 	int		i;
// 	int		nbr_elem;
// 	char test[] = "echo < test | < redir | ls -l -e -r > arr > plop > ppp < infile | ls -la didi > fdgdf";
	
	
// 	t_simple_command	*sentences;
// 	t_simple_command	*temp;

// 	printf("text: %s\n", test);
// 	printf("strlen: %ld\n", ft_strlen(test));

// 	len = nbr_words(test);
// 	printf("nbr_words: %d\n\n", len);

// 	i = 0;
// 	arr = ft_split_tokens(test);// semble ok
// 	typification(arr, len);//semble ok
// 	nbr_elem = nbr_pipe(arr, len);//semble ok
// 	sentences = creation_list_command(arr, len);
// 	ft_print_sentences(sentences);
// 	while (sentences)
// 	{
// 		temp = sentences;
// 		sentences = sentences->next;
// 		ft_free_3dtab(temp->args);
// 		ft_free_redir(&temp->redir);
// 		free(temp);
// 	}
// 	while (i < len)
// 	{
// 		// printf("\nvalue: %s\n", arr[i].value);
// 		// printf("type: %d\n", arr[i].type);
// 		// printf("fl_quotes: %d\n", arr[i].fl_quotes);
// 		free(arr[i].value);
// 		// free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }