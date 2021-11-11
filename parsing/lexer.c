#include <stdio.h>
#include "libft/libft.h"

typedef struct s_token
{
    char *type;
    void *valeur;
} t_token;

//J'ai fait comme si ton tableau se finissait par un membre NULL mais peut etre que tu preferes
//utiliser la size comme conditions d'arret
void    ft_print_tokens(t_token const **tab_tokens)
{
    int i;

    i = 0;
    while(tab_tokens[i])
        i++;
    printf("Tab contains %d tokens\n", i);
    i = 0;
    while (tab_tokens[i])
    {
        printf("Token n° %d is of type %s and contains the string : [%s]\n",
        i, tab_tokens[i]->type, tab_tokens[i]->valeur);
        i++;
    }
}

int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	while (power)
	{
		result *= nb;
		power--;
	}
	return (result);
}

int	like_log(int nb)
{
	int	res;

	res = 0;
	while (ft_power(2, res) < nb)
		res ++;
	return (res);
}

int    is_num(char *token)
{
    int len;
    int res;

    len = ft_strlen(token);
    res = like_log(ft_atoi(token));
    if (len == res)
        return (1);
    return (0);
}

int    is_command(char *token)
{
    return (0);
}

int    is_flag(char *token)
{
    return (0);
}

int    is_reserved_words(char *token)
{
    return (0);
}

int    is_quotes(char *token)
{
    return (0);
}

int    is_special_symbols(char *token)
{
    return (0);
}


char    *get_type(char *token)
{
    int len;
    int res;

    if (is_num(token))
        return("number");
    else if(is_command(token))
        return("commande");
    
}
// etc...

int get_tokens(char **tokens, int len, t_token **tab_tokens)
{
    int i;

    i = 0;
    while (i < len)
    {
        tab_tokens[i]->type = get_type(tokens[i]);
        tab_tokens[i]->valeur = tokens[i]; //en fonction du type mettre la valeur;
    }
}

int main(int argc, char **argv)
{
    char **tokens;
    t_token *tab_tokens;
    int nb_process;
    int len;

    char splitter[] = " \n\t";
    len = nbr_words(argv[1], splitter);
    tokens = ft_split(argv[1], splitter);
    nb_process = get_tokens(tokens, len, &tab_tokens);
    
}