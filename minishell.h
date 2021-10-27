#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

typedef struct s_simple_command
{
	int	args_num;
	char **args;
	char *cmd;
}				t_simple_command;

t_simple_command *ft_get_simple_command(char *str);

int	ft_strcmp(char *s1, char *s2);

int	ft_isbuiltin(char *str);

char	*ft_get_command(char *str);

char    **ft_get_args(char *str);

int ft_get_args_size(char **args);