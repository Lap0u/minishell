#ifndef LEXER_H
# define LEXER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_token
{
	int		type;
	char	*value;
	int		fl_quotes;
}				t_token;

# define COMMANDE 1
# define FLAG 2
# define ARG 3
# define PIPE 4
# define RED_OUT 5 // > 
# define RED_IN 6 // <
# define RED_OUT_APP 7 // >>
# define RED_HERE_DOC 8 // <<
# define DOLLAR 9 // substitution


# define COMMANDE 1

/*nbr_tockens.c*/

size_t	ft_strlen(const char *s);
int		in_charset(char letter);
int		nbr_words_s_quotes(char const *str, int *i);
int		nbr_words_dollar(char const *str, int *i);
int		nbr_words_double_quotes(char const *str, int *i);
int		nbr_words(char const *str);

/*ft_split_tokens.c*/
int		what_is_len_s_quotes(char *str);
int		what_is_len_double_quotes(char *str);
int		what_is_len_simple(char *str);
int		what_is_len(char *str);
char	*make_str(char *str);
void	make_str_dollar(char *str, t_token *my_arr, int *i, int *y);
void	make_str_s_quotes(char *str, t_token *my_arr, int *i, int *y);
void	check_str_double_quote(char *str, t_token *my_arr, int *i, int *y);
void	make_str_double_quote(char *str, t_token *my_arr, int *i, int *y);
void	make_str_simple(char *str, t_token *my_arr, int *i, int *y);
void	typification(t_token *my_arr, int nbr_token);
t_token	*ft_split_tokens(char *str);

#endif