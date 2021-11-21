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

int	what_is_len_s_quotes(char *str)
{
	int	len;

	len = 0;
	str++;
	while (*str && *str != '\'')
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len_double_quotes(char *str)
{
	int	len;

	len = 0;
	str++;
	while (*str && *str != '"' && *str != '$')
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len_simple(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0' && (*str != '\'' && *str != '"' && *str != '$')
		&& (!in_charset(*str)))
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len(char *str)
{
	int		i;
	char	*arr;

	i = 0;
	arr = str;
	if (*arr == '\0')
		return (0);
	if (*arr == '\'')
		i = what_is_len_s_quotes(str);
	else if (*arr == '"')
		i = what_is_len_double_quotes(str);
	else if (*arr != '$')
		i = what_is_len_simple(arr);
	else
	{
		i++;
		arr++;
		if (*arr != '\0' && *arr != '$')
			i += what_is_len_simple(arr);
		else if (*arr && *arr == '$')
			i++;
	}
	return (i);
}

char	*make_str(char *str)
{
	int		i;
	char	*arr;
	int		len;

	i = 0;
	len = what_is_len(str);
	// printf("len : %d\n", len);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (*str == '\'')
		str++;
	else if (*str == '"')
		str++;
	while (i < len)
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

void	make_str_dollar(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '$')
	{
		my_arr[*y].value = make_str(&str[*i]);
		*y = *y + 1;
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
}

void	make_str_s_quotes(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '\'' && str[*i + 1] != '\'')
	{
		my_arr[*y].value = make_str(&str[*i]);
		my_arr[*y].fl_quotes = 1;
		*y = *y + 1;
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i])
			*i = *i + 1;
		if (str[*i] && str[*i] == '\'')
			*i = *i + 1;
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
		*i = *i + 2;
}

void	check_str_double_quote(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i + 1] != '$')
	{
		my_arr[*y].value = make_str(&str[*i]);
		my_arr[*y].fl_quotes = 2;
		*y = *y + 1;
		*i = *i + 1;
	}
	else
		*i = *i + 1;
}

void	make_str_double_quote(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '"' && str[*i + 1] != '"')
	{
		check_str_double_quote(str, my_arr, i, y);
		while (str[*i] != '\0' && str[*i] != '"')
		{
			while (str[*i] != '\0' && str[*i] != '"' && str[*i] != '$')
				*i = *i + 1;
			if (str[*i] == '$')
				my_arr[*y].fl_quotes = 2;
			make_str_dollar(str, my_arr, i, y);
			if (str[*i] != '\0' && str[*i] != '\"' && str[*i] != '$')
			{
				str[*i - 1] = '"';
				my_arr[*y].value = make_str(&str[*i - 1]);
				my_arr[*y].fl_quotes = 2;
				*y = *y + 1;
			}
		}
		if (str[*i] == '"')
			*i = *i + 1;
	}
	else if (str[*i] == '"' && str[*i + 1] == '"')
		*i = *i + 2;
}

void	make_str_simple(char *str, t_token *my_arr, int *i, int *y)
{
	if ((str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i])))
		*i = *i + 1;
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i]) == 0))
	{
		my_arr[*y].value = make_str(&str[*i]);
		my_arr[*y].fl_quotes = 0;
		*y = *y + 1;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
			&& (!in_charset(str[*i])))
			*i = *i + 1;
	}
}

t_token	*ft_split_tokens(char *str)
{
	t_token	*my_arr;
	int		words;
	int		i;
	int		y;
	int		len;

	if (!str)
		return (malloc(0));
	y = 0;
	i = 0;
	len = ft_strlen(str);
	words = nbr_words(str);
	my_arr = (t_token *)malloc(sizeof(t_token) * words);
	if (my_arr == (void *)0)
		return ((void *)0);
	while (i < len && str[i])
	{
		make_str_simple(str, my_arr, &i, &y);
		if (str[i] == '$')
			my_arr[y].fl_quotes = 0;
		make_str_dollar(str, my_arr, &i, &y);
		make_str_s_quotes(str, my_arr, &i, &y);
		make_str_double_quote(str, my_arr, &i, &y);
	}
	// my_arr[y] = (void *)0;
	return (my_arr);
}

// int main(void)
// {
// 	t_token	*arr;
// 	int		len;
// 	int		i;

// 	char test[] = "'$$' ";
// 	printf("text: %s\n", test);
// 	printf("strlen: %ld\n", ft_strlen(test));

// 	len = nbr_words(test);
// 	printf("nbr_words: %d\n", len);

// 	i = 0;
// 	arr = ft_split_tokens(test);
	// while (i < len)
	// {
	// 	printf("value: %s\n", arr[i].value);
	// 	printf("fl_quotes: %d\n", arr[i].fl_quotes);
	// 	free(arr[i].value);
	// 	// free(arr[i]);
	// 	i++;
	// }
// 	free(arr);
// 	return (0);
// }
