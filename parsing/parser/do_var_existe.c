/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:55:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/09 15:56:22 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_redir(t_token *temp, int len, int y)
{
	while (y < len && temp[y].type >= RED_OUT && temp[y].type <= RED_HERE_DOC)
		y += 2;
	return (y);
}

int	do_var_existe(t_token **arr_tok, int len, char **env, int index)
{
	int		i;
	int		y;
	int		count;
	char	*str;
	t_token	*temp;

	count = 0;
	y = index;
	temp = *arr_tok;
	while (y < len)
	{
		y = skip_redir(temp, len, y);
		if (y == len || temp[y].type == PIPE)
			return (count);
		temp[y].subst = 0;
		i = 0;
		while (env[i])
		{
			str = ft_var_only(env[i]);
			if ((ft_strcmp(temp[y].value, "$?") == 0) || (temp[y].type == DOLLAR
					&& ft_strcmp(str, temp[y].value + 1) == 0)
				|| ((*(temp[y].value) == '$') && !*(temp[y].value + 1)))
			{
				count++;
				temp[y].subst = 1;
			}
			else if (temp[y].type == ARG)
			{
				count++;
				free(str);
				break ;
			}
			free(str);
			i++;
		}
		if (temp[y].type == DOLLAR && temp[y].subst == 0)
		{
			free(temp[y].value);
			temp[y].value = NULL;
		}
		y++;
	}
	return (count);
}
