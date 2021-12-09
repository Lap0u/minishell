/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:06:57 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/09 16:22:26 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_expandable(char *str, int red, int quote, char **env)
{
	int		i;
	char	*temp;

	if (str[0] != '$' || red == RED_HERE_DOC || quote == 1)
		return (1);
	if (quote != 1 && ft_strcmp(str, "$?") == 0)
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

int	is_there_red(t_token *tok, int ind, int len, char **env)
{
	while (ind < len && tok[ind].type != PIPE)
	{
		if (tok[ind].type == RED_HERE_DOC)
			return (0);
		else if (tok[ind].type >= RED_OUT
			&& tok[ind].type <= RED_HERE_DOC
			&& tok[ind + 1].fl_q == 1)
			return (0);
		else if (tok[ind].type >= RED_OUT
			&& tok[ind].type <= RED_HERE_DOC
			&& is_expandable(tok[ind + 1].value, 0, 0, env))
			return (0);
		ind++;
	}
	return (1);
}

void	new_redir(t_token *tok, t_redir **start)
{
	t_redir	*save;
	t_redir	*new;

	save = *start;
	while (save->next)
		save = save->next;
	new = malloc(sizeof(t_redir));
	if (new == NULL)
		return ;
	new->type = tok[0].type - 5;
	new->file = tok[1].value;
	new->next = NULL;
	save->next = new;
}

int	first_redir(t_redir **start, t_token *tok, int ind)
{
	(*start)->type = tok[ind].type -5;
	(*start)->next = NULL;
	if (tok[ind].type == RED_HERE_DOC || tok[ind + 1].fl_q == 1)
	{
		(*start)->file = tok[ind + 1].value;
		return (0);
	}
	return (-1);
}

int	is_good_redir(t_token *tok, int ind, char **env)
{
	if (tok[ind].type >= RED_OUT && tok[ind].type <= RED_HERE_DOC
		&& is_expandable(tok[ind + 1].value, tok[ind].type,
			tok[ind + 1].fl_q, env))
		return (1);
	return (0);
}

char	*call_expand(t_token *tok, int ind, char **env, int ret)
{
	return (ft_exp_dol(tok[ind + 1].value, tok[ind].type, env, ret));
}

t_redir	*ft_fill_redir(t_token *tok, int ind, int len, char **env, int ret)
{
	t_redir	*start;
	int		bool_start;

	bool_start = -1;
	if (is_there_red(tok, ind, tok[0].size, env) == 1)
		return (NULL);
	start = malloc(sizeof(t_redir));
	if (start == NULL)
		return (NULL);
	while (ind < tok[0].size && tok[ind].type != PIPE)
	{
		if (is_good_redir(tok, ind++, env))
		{
			if (bool_start == -1)
			{
				if (first_redir(&start, tok, ind - 1) != 0)
					start->file = call_expand(tok, ind - 1, env, ret);
			}
			else
				new_redir(&tok[ind - 1], &start);
			bool_start = 0;
			ind++;
		}
	}
	return (start);
}
