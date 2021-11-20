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
///////////////utils

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

void	ft_free_3dtab(char **tab) //////a uncomment quand dollar sera implemente
{
	// int i;

	// i = 0;
	// if (!tab)
	// 	return ;
	// // while (tab[i])
	// // {
	// // 	free(tab[i]);
	// // 	i++;
	// // }
	free(tab);
}

void	ft_free_redir(t_redir **list)
{
	t_redir *temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		// free(temp.file); //a uncomment quand dollar sera imple
		free(temp);
	}
	*list = NULL;
}

///////////////end

///////////////fill_args
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

char	**ft_fill_args(t_token *arr_tok, int index, int len)
{
	char	**args;
	int		nbr_args;
	int		i;

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
			args[i] = arr_tok[index].value; //expand si dollar ou args=arr.value si arg
			i++;
		}
		index++;
	}
	args[i] = (void *)0;
	return (args);
}
///////////////end

///////////////fill_redir

int	is_there_red(t_token *arr_tok, int index, int len)
{
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
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

t_redir	*ft_fill_redir(t_token *arr_tok, int index, int len)
{
	t_redir *start;
	int		bool_start;
	
	bool_start = -1;
	if (is_there_red(arr_tok, index, len) == 1)
		return ((void *)0);
	start = malloc(sizeof(t_redir));
	if (start == NULL)
		return ((void *)0);
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
		{
			if (bool_start == -1)
			{
				start->type = arr_tok[index].type - 5;
				start->file = arr_tok[index + 1].value; //expand si dollar ou args=arr.value si arg
				start->next = NULL;
				bool_start = 0;
			}
			else
				new_redir(&arr_tok[index], &start);
		}
		index++;
	}
	return (start);
}

///////////////


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
		my_elem->args_num = ft_2dlen(my_elem->args); ////
		my_elem->next = (void *)0;
	}
	return (my_elem);
}

void	add_new_elem(t_simple_command **start, t_token *arr_tok,
		int index, int len)
{
	t_simple_command *save;

	save = *start;
	while (save->next)
		save = save->next;
	save->next = new_elem(arr_tok, index, len);
}

t_simple_command *creation_list_command(t_token *arr_tok, int arr_len)
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
	return (lst_command);////
}

int main(void)
{
	t_token	*arr;
	int		len;
	int		i;
	int		nbr_elem;
	char test[] = "echo < test | < redir | ls -l -e -r > arr > plop > ppp < infile | ls -la didi > fdgdf";
	
	
	t_simple_command	*sentences;
	t_simple_command	*temp;

	printf("text: %s\n", test);
	printf("strlen: %ld\n", ft_strlen(test));

	len = nbr_words(test);
	printf("nbr_words: %d\n\n", len);

	i = 0;
	arr = ft_split_tokens(test);// semble ok
	typification(arr, len);//semble ok
	nbr_elem = nbr_pipe(arr, len);//semble ok
	sentences = creation_list_command(arr, len);
	ft_print_sentences(sentences);
	while (sentences)
	{
		temp = sentences;
		sentences = sentences->next;
		ft_free_3dtab(temp->args);
		ft_free_redir(&temp->redir);
		free(temp);
	}
	while (i < len)
	{
		// printf("\nvalue: %s\n", arr[i].value);
		// printf("type: %d\n", arr[i].type);
		// printf("fl_quotes: %d\n", arr[i].fl_quotes);
		free(arr[i].value);
		// free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}