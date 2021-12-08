/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:24:10 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/08 11:30:44 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	what_is_len(char *str, int fl_quotes)
{
	int		i;
	char	*arr;

	i = 0;
	arr = str;
	if (*arr == '\0')
		return (0);
	if (*arr == '\'' && fl_quotes == 1)
		i = what_is_len_s_quotes(str);
	else if (*arr == '"' || fl_quotes == 2)
		i = what_is_len_double_quotes(str);
	else if (*arr != '$' && (*arr != '<' && *arr != '>'))
		i = what_is_len_simple(arr);
	else if (*arr == '$')
		i = what_is_len_dollar(arr);
	else if (*arr == '<' || *arr == '>')
		i = what_is_len_redir(arr);
	else
	{
		i++;
		arr++;
		if (*arr != '\0' && *arr != '$')
			i += what_is_len_simple(arr);
	}
	return (i);
}

void	make_str_body(char *arr, char *str, int *i, int len)
{
	if (str[*i] && ((str[*i + 1] == '"' && str[*i + 2] == '"')
			|| (str[*i + 1] == '\'' && str[*i + 2] == '\'')))
	{
		while (*i < len)
		{
			arr[*i] = str[*i];
			*i += 1;
		}
	}
	else
	{
		while (*i < len && str[*i] != '"' && str[*i] != '\'')
		{
			arr[*i] = str[*i];
			*i += 1;
		}
		if (str[*i] == '"' || str[*i] == '\'')
		{
			while (*i < len)
			{
				arr[*i] = ' ';
				*i += 1;
			}	
		}
	}
}

int	make_str_check(char *arr, char **str, int *i, int fl_quotes)
{
	if (**str == '\'' && *(*str + 1) == '\'')
	{
		arr[*i] = '\0';
		return (0);
	}
	else if (**str == '"' && *(*str + 1) == '"')
	{
		arr[*i] = '\0';
		return (0);
	}
	else if (**str == '\'' && *(*str + 1) != '\'' && fl_quotes != 2)
		*str = *str + 1;
	else if (**str == '"' && *(*str + 1) != '"')
		*str = *str + 1;
	return (1);
}

char	*make_str(char *str, int fl_quotes)
{
	int		i;
	char	*arr;
	int		len;

	i = -1;
	len = what_is_len(str, fl_quotes);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (make_str_check(arr, &str, &i, fl_quotes))
	{
		if (*str == '"' && fl_quotes != 2)
			while (++i < len)
				arr[i] = str[i];
		else if (fl_quotes != 2)
			make_str_body(arr, str, &i, len);
		else
		{
			while (++i < len && str[i] != '"')
				arr[i] = str[i];
		}
	}
	arr[i] = '\0';
	return (arr);
}

t_token	*ft_split_tokens(char *str, int nbr_tokens)
{
	t_token	*my_arr;
	int		i;
	int		y;

	if (!str)
		return (malloc(0));
	y = 0;
	i = 0;
	my_arr = (t_token *)malloc(sizeof(t_token) * (nbr_tokens + 1));
	if (my_arr == (void *)0)
		return ((void *)0);
	while (i < ft_strlen(str) && str[i])
	{
		make_str_simple(str, my_arr, &i, &y);
		make_str_redir(str, my_arr, &i, &y);
		if (str[i] == '$')
			my_arr[y].fl_quotes = 0;
		make_str_dollar(str, my_arr, &i, &y);
		make_str_s_quotes(str, my_arr, &i, &y);
		make_str_double_quote(str, my_arr, &i, &y);
	}
	my_arr[nbr_tokens].fl_quotes = -1;
	typification(my_arr, nbr_tokens);
	return (my_arr);
}
