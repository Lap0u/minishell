/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:04 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/09 16:23:44 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_there_red(t_token *tok, int ind, int len, char **env)
{
	while (ind < len && tok[ind].type != PIPE)
	{
		if (tok[ind].type == RED_HERE_DOC)
			return (0);
		else if (tok[ind].type >= RED_OUT
			&& tok[ind].type <= RED_HERE_DOC
			&& tok[ind + 1].fl_quotes == 1)
			return (0);
		else if (tok[ind].type >= RED_OUT
			&& tok[ind].type <= RED_HERE_DOC
			&& is_expandable(tok[ind + 1].value, 0, 0, env))
			return (0);
		ind++;
	}
	return (1);
}

int	is_good_redir(t_token *tok, int ind, char **env)
{
	if (tok[ind].type >= RED_OUT && tok[ind].type <= RED_HERE_DOC
		&& is_expandable(tok[ind + 1].value, tok[ind].type,
			tok[ind + 1].fl_quotes, env))
		return (1);
	return (0);
}

char	*call_expand(t_token *tok, int ind, char **env, int ret)
{
	return (ft_expand_dollar(tok[ind + 1].value, tok[ind].type, env, ret));
}
