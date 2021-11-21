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

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

int	in_charset(char letter)
{
	if (letter == ' ' || letter == '\t' || letter == '\n')
		return (1);
	return (0);
}

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
		else if (str[*i] == 0)//////////////added by clement
		{
			write(2,"Error: There is not second single quotes\n", 41);
			exit(1);
		}////////end added
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
		*i = *i + 2;
	return (words);
}

int	nbr_words_dollar(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '$')
	{
		words++;
		*i = *i + 1;
		if (str[*i] && str[*i] != '$')
		{
			while (str[*i] && (str[*i] != '\'' && str[*i] != '"'
					&& str[*i] != '$') && (!in_charset(str[*i])))
				*i = *i + 1;
		}
		else if (str[*i] && str[*i] == '$')
			*i = *i + 1;
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
		while (str[*i] && str[*i] != '"')
		{
			while (str[*i] && str[*i] != '"' && str[*i] != '$')
				*i = *i + 1;
			words += nbr_words_dollar(str, i);
			if (str[*i] != '\"' && str[*i] != '$')
				words++;
		}
		if (str[*i] == '"')
			*i = *i + 1;
		else
		{
			write(2,"Error: There is not second duble quotes\n", 40);
			exit(1);
		}
	}
	return (words);
}

int	nbr_words(char const *str)
{
	int	words;
	int	i;
	int	len;

	words = 0;
	i = 0;
	len = (int)ft_strlen(str);
	while ((i < len) && str[i])
	{
		if ((str[i] != '\'' && str[i] != '"' && str[i] != '$')
			&& (in_charset(str[i])))
			i++;
		if (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != '$')
			&& (in_charset(str[i]) == 0))
		{
			words++;
			while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != '$')
				&& (!in_charset(str[i])))
				i++;
		}
		words += nbr_words_dollar(str, &i);
		words += nbr_words_s_quotes(str, &i);
		words += nbr_words_double_quotes(str, &i);
	}
	return (words);
}

// int main(int argc, char **argv)
// {
// 	// char **arr;
// 	int len;
// 	// int i;
// 	(void)argc;
// 	(void)argv;

// 	char test[] = "'dfgj  $$ h;g  d' \" $$ $$ \" $$$$";
// 	printf("ft_strlen = %ld_\n", ft_strlen(test));

// 	len = nbr_words(test);
// 	printf("nbr_words = %d_\n", len);

// 	// i = 0;
// 	// arr = ft_split_tokens(test);
// 	// while (i < len)
// 	// {
// 	// 	printf("%s\n",arr[i]);
// 	// 	i++;
// 	// }
// 	// printf("\n%s\n", "$USER");
// 	return (0);
// }