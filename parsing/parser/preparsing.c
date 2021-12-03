/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:24:10 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/03 12:15:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_arrtok(t_token *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i].type >= RED_OUT && tab[i].type <= RED_HERE_DOC)
			free(tab[i].value);
		i++;
	}
	free(tab);
}

t_simple_command	*new_elem(t_token *arr_tok, int index, int len, char **env, int ret)
{
	t_simple_command	*my_elem;

	my_elem = (void *)0;
	my_elem = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (my_elem != (void *)0)
	{
		my_elem->last_ret = ret;
		my_elem->redir = ft_fill_redir(arr_tok, index, len, env, ret);
		my_elem->args = ft_fill_args(arr_tok, index, len, env, ret);
		my_elem->cmd = my_elem->args[0];
		my_elem->args_num = ft_2dlen(my_elem->args);
		my_elem->next = (void *)0;
	}
	return (my_elem);
}

void	add_new_elem(t_simple_command **st, t_token *arr_tok, int ind, int len, char **env, int ret)
{
	t_simple_command	*save;

	save = *st;
	while (save->next)
		save = save->next;
	save->next = new_elem(arr_tok, ind, len, env, ret);
}

void	add_env_in_elem(t_simple_command *lst_command, char **env)
{
	t_simple_command	*temp;
	int					i;

	i = 0;
	temp = lst_command;
	while (temp)
	{
		temp->env = env;
		temp->pos = i++;
		ft_open_files(temp, temp->redir);
		temp = temp->next;
	}
}

t_simple_command	*creation_list_command(t_token *arr_tok, int arr_len, char **env, int last_ret)
{
	int					nbr_elem;
	t_simple_command	*lst_command;
	int					i;
	int					index;

	index = 0;
	nbr_elem = nbr_pipe(arr_tok, arr_len);
	if (nbr_elem < 0)
		return ((void *)0);
	lst_command = NULL;
	lst_command = new_elem(arr_tok, index, arr_len, env, last_ret);
	index = skip_topipe(arr_tok, index, arr_len);
	if (lst_command == (void *)0)
		return ((void *)0);
	i = 1;
	while (i < nbr_elem)
	{
		add_new_elem(&lst_command, arr_tok, index, arr_len, env, last_ret);
		index = skip_topipe(arr_tok, index, arr_len);
		i++;
	}
	add_env_in_elem(lst_command, env);
	ft_free_arrtok(arr_tok, arr_len);
	return (lst_command);
}
