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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	in_charset(char letter)
{
	if (letter == ' ' || letter == '\t' || letter == '\n')
		return (1);
	return (0);
}



int	nbr_words(char const *str)
{
	int	words;
	int i;
	int len;

	words = 0;
	i = -1;
	len = (int)ft_strlen(str);
	while (++i < len)
	{
		if ((str[i] != '\'' && str[i] != '"' && str[i] != '$') && (in_charset(str[i])))
			i++;
		if ((str[i] != '\'' && str[i] != '"' && str[i] != '$') && (!in_charset(str[i])))
		{
			words++;
			while ((str[i] != '\'' && str[i] != '"' && str[i] != '$') && (!in_charset(str[i])))
				i++;
		}
		if (str[i] == '$')
		{
			words++;
			i++;
			while ((str[i] != '\'' && str[i] != '"'&& str[i] != '$') && (!in_charset(str[i])))
				i++;
		}
		if (str[i] == '\'')
		{
			words++;
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			words++;
			i++;
			while (str[i] != '"')
			{ 
				if (str[i] == '$')
				{
					words++;
					i++;
					while ((str[i] != '\'' && str[i] != '"' && str[i] != '$') && (!in_charset(str[i])))
						i++;
					if (str[i] != '"' && str[i] != '$')
					words++;
				}
				while (str[i] != '"' && str[i] != '$') 
					i++;
			}
		}
	}
	return (words);
}

char	*make_str(char *str, int indic)
{
	int		i;
	char	*arr;
	char 	*cp;
	int		flag;

	flag = 0;
	i = 0;
	cp = str;
	if (*cp == '\'' || *cp == '"' || *cp == '$')
	{
		if (*cp == '\'')
			flag = 1;
		else if (*cp == '"')
			flag = 2;
		// else if (*cp == '$')
		// 	flag = 3;
		cp++;
	}
	while (((cp[i] && !(in_charset(cp[i])) && cp[i] != '\'' && cp[i] != '"' && cp[i] != '$')))
		i++;
	if (flag == 3)
		i++;
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (arr == NULL)
		return ((void *)0);
	i = 0;
	if (flag == 1)
	{
		while (((cp[i] && cp[i] != '\'')))
		{
			arr[i] = cp[i];
			i++;
		}
	}
	else if (flag == 2)
	{
		while (((cp[i] && cp[i] != '"' && cp[i] != '$')))
		{
			arr[i] = cp[i];
			i++;
		}
	}
	else
	{
		if (indic)
		{
			while (((cp[i] && cp[i] != '"' && cp[i] != '$')))
			{
				arr[i] = cp[i];
				i++;
			}
		}
		else
		{
			// write(1, "1\n", 2);
			if (cp[i] == '$')
			{
				arr[i] = cp[i];
				i++;
			}
			while (((cp[i] && !(in_charset(cp[i])) && cp[i] != '\'' && cp[i] != '"' && cp[i] != '$')))
			{
				arr[i] = cp[i];
				i++;
			}
			// write(1, arr, ft_strlen(arr));
		}
	}
	arr[i] = '\0';
	return (arr);
}

char	**ft_split_tokens(char *s)
{
	char	**my_arr;
	int		words;
	int 	y;

	if (!s)
		return (malloc(0));
	y = 0;
	words = nbr_words(s);
	my_arr = (char **)malloc(sizeof(char *) * words + 1);
	if (my_arr == (void *)0)
		return ((void *)0);
	while (*s)
	{
		if ((*s != '\'' && *s != '"' && *s != '$') && (in_charset(*s)))
			s++;
		if ((*s != '\'' && *s != '"' && *s != '$') && (!in_charset(*s)))
		{
			my_arr[y] = make_str(s , 0);
			y++;
			while ((*s != '\'' && *s != '"' && *s != '$') && (!in_charset(*s)))
				s++;
		}
		if (*s == '$')
		{
			my_arr[y] = make_str(s, 0);
			y++;
			s++;
			while ((*s != '\'' && *s != '"' && *s != '$') && (!in_charset(*s)))
				s++;
		}
		if (*s == '\'')
		{
			my_arr[y] = make_str(s, 0);
			y++;
			s++;
			while (*s != '\'')
				s++;
		}
		if (*s == '"')
		{
			my_arr[y] = make_str(s, 0);
			y++;
			s++;
			while (*s != '"')
			{ 
				if (*s == '$')
				{
					my_arr[y] = make_str(s, 0);
					y++;
					s++;
					while ((*s != '\'' && *s != '"' && *s != '$') && (!in_charset(*s)))
						s++;
					if (*s != '"' && *s != '$')
					{
						my_arr[y] = make_str(s, 1);
						y++;
						s++;
					}
				}
				while (*s != '"' && *s != '$') 
					s++;
			}
		}
		s++;
	}
	my_arr[y] = (void *)0;
	return (my_arr);
}

int main(int argc, char **argv)
{
	char **arr;
	int len;
	int i;
	(void)argc;
	(void)argv;

	char test[] = "Olga \"$USER$\"";
	printf("%ld\n", ft_strlen(test));

	len = nbr_words(test);
	printf("%d\n", len);

	i = 0;
	arr = ft_split_tokens(test);
	while (i < len)
	{
		printf("%s\n",arr[i]);
		i++;
	}
	printf("\n%s\n", "$USER");
	return (0);
}
