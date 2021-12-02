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
	if (*str == '\'' && *(str + 1) == '\'')
		len++;
	else
	{
		str++;
		while (*str && *str != '\'')
		{
			len++;
			str++;
		}
	}
	return (len);
}

int	what_is_len_double_quotes(char *str)
{
	int	len;

	len = 0;
	
	if (*str == '\'' && *(str + 1) == '\'')
		len++;
	else
	{
		str++;
		while (*str && *str != '"' && *str != '$')
		{
			len++;
			str++;
		}
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
	// printf("65: len_simple: %d, *str = %c\n", len, *str);
	// len += nbr_spaces_add(str);
	return (len);
}




int	what_is_len_dollar(char *str)
{
	int	len;

	len = 1;
	str++;
	// printf("75: *str - 1 =  %c\n", *(str - 1));
	if (*str && ((*str == '"' && *(str + 1) == '"') || (*str == '\'' && *(str + 1) == '\'')))
		len += 2;
	else if (*str && *str == '$')
		len++;
	else if (*str && *str == '?')
		len++;
	else if (*str && (*str != '\'' && *str != '"'
					&& *str != '$') && (!in_charset(*str)) && *str != '_' && !ft_isalpha(*str))
		len++;
	else if (*str && (*str == '_' || ft_isalpha(*str)))
	{
		while (*str && (*str == '_' || ft_isalpha(*str)))
		{
			len++;
			str++;
		}
	}
		// len += what_is_len_simple(str);
	return (len);
}

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
	else if (*arr != '$')
		i = what_is_len_simple(arr);
	else if (*arr == '$')
		i = what_is_len_dollar(arr);
	else
	{
		// write(1, "m_\n", 3);
		i++;
		arr++;
		if (*arr != '\0' && *arr != '$')
			i += what_is_len_simple(arr);
	}
	return (i);
}

char	*make_str(char *str, int fl_quotes)
{
	int		i;
	char	*arr;
	int		len;

	i = 0;
	len = what_is_len(str, fl_quotes);
	// printf("len1 : %d\n", len);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (*str == '\'' && *(str + 1) == '\'')
	{
		arr[i] = '\0';
		// printf("str = %s, len = %d\n", arr, ft_strlen(arr));
		return (arr);
	}
	else if (*str == '"' && *(str + 1) == '"')
	{
		arr[i] = '\0';
		return (arr);
	}
	else if (*str == '\'' && *(str + 1) != '\'' && fl_quotes != 2)
		str++;
	else if (*str == '"' && *(str + 1) != '"')
		str++;
	// else if (*str == '"')
	// 	str++;
	if (fl_quotes != 2)
	{
		// printf("149: %c\n", str[i]);
		if (str[i] && ((str[i + 1] == '"' && str[i + 2] == '"') || (str[i + 1] == '\'' && str[i + 2] == '\'')))
		{
			while (i < len)
			{
				// printf("153: %c\n", str[i]);
				arr[i] = str[i];
				i++;
			}
		}
		else
		{
			while (i < len && str[i] != '"' && str[i] != '\'')
			{
				arr[i] = str[i];
				i++;
			}
			if (str[i] == '"' || str[i] == '\'')
			{
				while (i < len)
				{
					arr[i] = ' ';
					i++;
				}	
			}
		}
	}
	else
	{
		while (i < len && str[i] != '"')
		{
			arr[i] = str[i];
			i++;
		}
	}
	arr[i] = '\0';
	return (arr);
}

void	make_str_dollar(char *str, t_token *my_arr, int *i, int *y)
{
	// printf("make_str_dollar: fl_quotes = %d, *str = %c\n", my_arr[*y].fl_quotes, *str);
	// int j;

	// j = 0;
	if (str[*i] == '$')
	{
		// if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
		// 			&& str[*i] != '$') && (!in_charset(str[*i])) && (str[*i] != '_' || !ft_isalpha(str[*i])))
		// {
		// 	my_arr[*y].value = (char *)malloc(sizeof(char) * 3);
		// 	while (j < 2)
		// 	{
		// 		my_arr[*y].value[j++] = str[*i++];
		// 	}
		// 	my_arr[*y].fl_space = 0;
		// 	if (str[*i] == ' ' && my_arr[*y].fl_quotes != 2)
		// 		my_arr[*y].fl_space = 1;
		// }
		
		// {
			// printf("189: coucou\n");
			my_arr[*y].value = make_str(&str[*i], 0);
			*i = *i + 1;
			my_arr[*y].fl_space = 0;
			if (str[*i] && ((str[*i] == '"' && str[*i + 1] == '"') || (str[*i] == '\'' && str[*i + 1] == '\'')))
			{
				// printf("216: %c\n", str[*i]);
				*i = *i + 2;
				if (str[*i] == ' ' && my_arr[*y].fl_quotes != 2)
					my_arr[*y].fl_space = 1;
				// printf("220: %c\n", str[*i]);
			}			
			else if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
					&& str[*i] != '$'))
			{
				// printf("201: *str = %c\n", str[*i]);
				if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
					&& str[*i] != '$') && (!in_charset(str[*i])) && (str[*i] == '_' || ft_isalpha(str[*i])))
				{
					while (str[*i] && (str[*i] != '\'' && str[*i] != '"'
					&& str[*i] != '$') && (!in_charset(str[*i])) && (str[*i] == '_' || ft_isalpha(str[*i])))
						*i = *i + 1;
				}
				else
					*i = *i + 1;
				// printf("211: *str = %c\n", str[*i]);
				if (str[*i] == ' ' && my_arr[*y].fl_quotes != 2)
					my_arr[*y].fl_space = 1; 
			}
			else if (str[*i] && str[*i] == '$')
			{
				*i = *i + 1;
				if (str[*i] == ' ' && my_arr[*y].fl_quotes != 2)
					my_arr[*y].fl_space = 1;
			}	
		// }
		*y = *y + 1;
	}
}

void	make_str_s_quotes(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '\'' && str[*i + 1] != '\'')
	{
		my_arr[*y].value = make_str(&str[*i], 1);
		my_arr[*y].fl_quotes = 1;
		my_arr[*y].fl_space = 0;
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i])
			*i = *i + 1;
		if (str[*i] && str[*i] == '\'')
			*i = *i + 1;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
	{
		// write(1, "m_\n", 3);
		my_arr[*y].value = make_str(&str[*i], 1);
		*i = *i + 2;
		my_arr[*y].fl_quotes = 1;
		my_arr[*y].fl_space = 0;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
	
}

void	check_str_double_quote(char *str, t_token *my_arr, int *i, int *y)
{
	// printf("str[i] = %c, str[i + 1] = %c\n",str[*i], str[*i + 1]);
	if (str[*i + 1] != '$')
	{
		// printf("str[i] = %c, str[i + 1] = %c\n",str[*i + 1], str[*i]);
		my_arr[*y].value = make_str(&str[*i], 2); // a voir
		my_arr[*y].fl_quotes = 2;
		my_arr[*y].fl_space = 0;
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
		// printf("228: my_arr[y - 1] = %s, *str = %c\n", my_arr[*y -1].value, str[*i]);
		while (str[*i] && str[*i] != '\0' && str[*i] != '"')
		{
			while (str[*i] != '\0' && str[*i] != '"' && str[*i] != '$')
				*i = *i + 1;
			if (str[*i] == '$')
			{
				printf("str[i] = %c\n", str[*i]);
				my_arr[*y].fl_quotes = 2;
			}
			make_str_dollar(str, my_arr, i, y);
			printf("fl_quotes = %d\n", my_arr[*y - 1].fl_quotes);
			printf("str[i]1 = %c\n", str[*i]);
			if (str[*i] != '\0' && str[*i] != '\"' && str[*i] != '$')
			{
				my_arr[*y].fl_space = 0;
				my_arr[*y].fl_quotes = 2;
				my_arr[*y].value = make_str(&str[*i], my_arr[*y].fl_quotes);
				*y = *y + 1;
			}
		}
		// printf("249: my_arr[y - 1] = %s, *str = %c\n", my_arr[*y -1].value, str[*i]);
		if (str[*i] == '"')
			*i = *i + 1;
		// printf("252: my_arr[y - 1] = %s, *str = %c\n", my_arr[*y -1].value, str[*i]);
		if (str[*i] == ' ')
			my_arr[*y - 1].fl_space = 1;
		// printf("255: my_arr[y - 1] = %s, fl_space = %d\n", my_arr[*y -1].value, my_arr[*y - 1].fl_space);
	}
	else if (str[*i] == '"' && str[*i + 1] == '"')
	{
		// write(1, "v_\n", 3);
		my_arr[*y].value = make_str(&str[*i], 1);
		*i = *i + 2;
		my_arr[*y].fl_quotes = 2;
		my_arr[*y].fl_space = 0;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
	// printf("my_arr[*y].value = %s, my_arr[*y].fl_space = %d, my_arr[*y].fl_quotes = %d\n", my_arr[*y - 1].value,my_arr[*y - 1].fl_space, my_arr[*y - 1].fl_quotes);
}

// int	nbr_spaces_add(char *str)
// {
// 	int	i;
// 	int	nbr;

// 	i = 0;
// 	nbr = 0;
// 	while(((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i + 1] == '\'')))
// 	{
// 		i += 2;
// 		if (str[i] == ' ')
// 		{
// 			nbr++;
// 			write(1, "m_\n", 3);
// 			while (str[i] == ' ')
// 				i++;
// 		}
		
// 	}
// 	return (nbr);
// }

void	make_str_simple(char *str, t_token *my_arr, int *i, int *y)
{
	if ((str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i])))
		*i = *i + 1;
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i]) == 0))
	{
		my_arr[*y].value = make_str(&str[*i], 1);
		my_arr[*y].fl_quotes = 0;
		my_arr[*y].fl_space = 0;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
			&& (!in_charset(str[*i])))
			*i = *i + 1;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
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
	// printf("len = %d\n", len);
	words = nbr_words(str);
	my_arr = (t_token *)malloc(sizeof(t_token) * (words + 1));
	if (my_arr == (void *)0)
		return ((void *)0);
	while (i < len && str[i])
	{
		// printf("367: *Str = %c\n", str[i]);
		make_str_simple(str, my_arr, &i, &y);
		if (str[i] == '$')
			my_arr[y].fl_quotes = 0;
		make_str_dollar(str, my_arr, &i, &y);
		make_str_s_quotes(str, my_arr, &i, &y);
		make_str_double_quote(str, my_arr, &i, &y);
	}
	my_arr[words].fl_quotes = -1;
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
