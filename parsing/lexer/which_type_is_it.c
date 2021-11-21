
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


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


int	which_type(t_token *my_arr)
{
	if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '|' && my_arr->fl_quotes == 0)
		return (PIPE);
	else if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '>' && my_arr->fl_quotes == 0)
		return (RED_OUT);
	else if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '<' && my_arr->fl_quotes == 0)
		return (RED_IN);
	else if (ft_strlen(my_arr->value) == 2 && (ft_strncmp(">>",my_arr->value, 2) == 0) && my_arr->fl_quotes == 0)
		return (RED_OUT_APP);
	else if (ft_strlen(my_arr->value) == 2 && (ft_strncmp("<<",my_arr->value, 2) == 0) && my_arr->fl_quotes == 0)
		return (RED_HERE_DOC);
	else if ((ft_strncmp("$",my_arr->value, 1) == 0) && my_arr->fl_quotes != 1)
		return (DOLLAR);
	else
		return (ARG);
	return (0);
}

void	typification(t_token *my_arr, int nbr_token)
{
	int i;

	i = 0;
	while (i < nbr_token)
	{
		my_arr[i].type = which_type(&(my_arr[i]));
		// printf("return = %d\n", which_type(&(my_arr[i])));
		i++;
	}
}

// int main(void)
// {
// 	t_token	*arr;
// 	int		len;
// 	int		i;

// 	char test[] = "| >> << > < '$' \"$$\" $$";
// 	printf("text: %s\n", test);
// 	printf("strlen: %ld\n", ft_strlen(test));

// 	len = nbr_words(test);
// 	printf("nbr_words: %d\n", len);

// 	i = 0;
// 	arr = ft_split_tokens(test);
// 	typification(arr, len);
// 	while (i < len)
// 	{
// 		printf("value: %s\n", arr[i].value);
// 		printf("fl_quotes: %d\n", arr[i].fl_quotes);
// 		printf("type: %d\n", arr[i].type);
// 		free(arr[i].value);
// 		// free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (0);
// }
