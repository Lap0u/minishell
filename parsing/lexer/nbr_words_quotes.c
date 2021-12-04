/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_words_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:51:44 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 11:51:46 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nbr_words_s_quotes(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '\'' && str[*i + 1] != '\'')
	{
		words++;
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i])
			*i = *i + 1;
		if (str[*i] && str[*i] == '\'')
			*i = *i + 1;
		else if (str[*i] == 0)
		{
			write(2, "Error: There is not second single quotes\n", 41);
			return (-1);
		}
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
	{
		words++;
		*i = *i + 2;
	}
	return (words);
}

int	mouve_index(char const *str, int *i)
{
	int	words;

	words = 0;
	printf("mouve ind = %c, %i\n", str[*i], *i);
	while (str[*i] && str[*i] != '"')
	{
		while (str[*i] && str[*i] != '"' && str[*i] != '$')
			*i = *i + 1;
		words += nbr_words_dollar(str, i);
		if (str[*i] != '\"' && str[*i] != '$')
			words++;
	}
	return (words);
}

int	nbr_words_double_quotes(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '"')
	{
		*i = *i + 1;
		if (str[*i] != '\"' && str[*i] != '$')
			words++;
		words += mouve_index(str, i);
		if (str[*i] == '"' && str[*i - 1] == '"')
		{
			words++;
			*i = *i + 1;
		}
		else if (str[*i] == '"' && str[*i - 1] != '"')
			*i = *i + 1;
		else
		{
			write(2, "Error: There is not second duble quotes\n", 40);
			return (-2);
		}
	}
	return (words);
}
