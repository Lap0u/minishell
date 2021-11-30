int	nbr_words_double_quotes(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '"' && str[*i + 1] != '"')
	{
		printf("87: nbr_words_double_quotes, *Str = %c\n", str[*i]);
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
			*i = *i + 1;
		}
		// if (str[*i] == '"' && str[*i - 1] != '$')
		// {
		// 	printf("100: nbr_words_double_quotes = %d\n", words);
		// 	words++;
		// 	*i = *i + 1;
		// }
		if (str[*i] == '"' && str[*i - 2] == '$')
			*i = *i + 1;
		if (str[*i - 1] != '"')
		{
			write(2,"Error: There is not second duble quotes\n", 40);
			exit(1);
		}
	}
	else if (str[*i] == '"' && str[*i + 1] == '"')
	{
		words++;
		*i = *i + 2;
	}