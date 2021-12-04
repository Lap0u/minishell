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

int	in_charset(char letter)
{
	if (letter == ' ' || letter == '\t' || letter == '\n')
		return (1);
	return (0);
}

int	nbr_words_dollar(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '$')
	{
		words++;
		*i = *i + 1;
		if (str[*i] && ((str[*i] == '"' && str[*i + 1] == '"')
				|| (str[*i] == '\'' && str[*i + 1] == '\'')))
			*i = *i + 2;
		// else if (str[*i] && (str[*i] == '?' || str[*i] == '0'))
		// 	*i = *i + 1;
		else if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
			&& str[*i] != '$') && (!in_charset(str[*i]))
		&& (str[*i] == '_' || ft_isalpha(str[*i])))
		{
				*i = *i + 1;
			while (str[*i] && (str[*i] != '\'' && str[*i] != '"'
					&& str[*i] != '$') && (!in_charset(str[*i]))
				&& (str[*i] == '_' || ft_isalpha(str[*i]) || ft_isdigit(str[*i])))
					*i = *i + 1;
		}
		else if (str[*i] && str[*i] == '$')
			*i = *i + 1;
		else if (str[*i])
			*i = *i + 1;
	}
	printf("dollr words = %d, str = %c, i = %d\n", words, str[*i], *i);
	return (words);
}

int	nbr_words_redir(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '>')
	{
		words++;
		*i = *i + 1;
		if (str[*i] == '>')
			*i = *i + 1;
	}
	else if (str[*i] == '<')
	{
		words++;
		*i = *i + 1;
		if (str[*i] == '<')
			*i = *i + 1;
	}
	return (words);
}

int	nbr_words_simple(char const *str, int *i)
{
	int	words;

	words = 0;
	if ((str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i])))
		*i = *i + 1;
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i]) == 0) && str[*i] != '>' && str[*i] != '<')
	{
		words++;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
			&& (!in_charset(str[*i])) && str[*i] != '>' && str[*i] != '<')
			*i = *i + 1;
	}
	return (words);
}

int	nbr_words(char const *str)
{
	int	words;
	int	i;
	int	len;
	int	check;

	words = 0;
	i = 0;
	check = 0;
	len = (int)ft_strlen(str);
	while ((i < len) && str[i])
	{
		words += nbr_words_simple(str, &i);
		words += nbr_words_dollar(str, &i);
		words += nbr_words_redir(str, &i);
		check = nbr_words_s_quotes(str, &i);
		if (check < 0)
			return (check);
		words += check;
		check = nbr_words_double_quotes(str, &i);
		if (check < 0)
			return (check);
		words += check;
	}
	return (words);
}
