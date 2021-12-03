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
		&& (!in_charset(*str)) && *str != '>' && *str != '<')
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len_dollar(char *str)
{
	int	len;

	len = 1;
	str++;
	if (*str && ((*str == '"' && *(str + 1) == '"')
			|| (*str == '\'' && *(str + 1) == '\'')))
		len += 2;
	else if (*str && *str == '$')
		len++;
	else if (*str && *str == '?')
		len++;
	else if (*str && (*str != '\'' && *str != '"'
			&& *str != '$') && (!in_charset(*str))
		&& *str != '_' && !ft_isalpha(*str))
		len++;
	else if (*str && (*str == '_' || ft_isalpha(*str)))
	{
		while (*str && (*str == '_' || ft_isalpha(*str)))
		{
			len++;
			str++;
		}
	}
	return (len);
}

int	what_is_len_redir(char *str)
{
	int	len;

	len = 0;
	if (*str == '>')
	{
		len++;
		str++;
		if (*str == '>')
			len++;
	}
	else if (*str == '<')
	{
		len++;
		str++;
		if (*str == '<')
			len++;
	}
	return (len);
}
