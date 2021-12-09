/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_parser_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:51:01 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/09 17:51:05 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_fill_args_check_var_not_exist(t_token *arr_tok, int ind)
{
	if (arr_tok[ind].type == DOLLAR && arr_tok[ind].subst == 0
		&& arr_tok[ind].fl_space == 1 && (arr_tok[ind].fl_q == 2))
		return (1);
	else
		return (0);
}

int	ft_fill_args_check_expand(t_token *arr_tok, int ind)
{
	if (((arr_tok[ind].type == DOLLAR && arr_tok[ind].subst == 1)
			|| arr_tok[ind].type == ARG))
		return (1);
	else
		return (0);
}

int	ft_fill_args_check_spaces(t_token *arr_tok, int ind)
{
	if ((((arr_tok[ind].fl_space == 0 && (arr_tok[ind + 1].fl_q == 2
						|| arr_tok[ind + 1].fl_q == 1))
				&& ind < (arr_tok[0].size - 1))
			|| ((arr_tok[ind].fl_space == 0
					&& arr_tok[ind + 1].fl_q == 0)
				&& ind < (arr_tok[0].size - 1)))
		&& ((arr_tok[ind + 1].type < 5)
			|| (arr_tok[ind + 1].type > 8)))
		return (1);
	else
		return (0);
}