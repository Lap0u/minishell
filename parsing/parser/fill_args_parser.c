#include "../../minishell.h"

int		ft_count_args(t_token *arr_tok, int index, int len)
{
	int count;

	count = 0;
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (arr_tok[index].type == DOLLAR || arr_tok[index].type == ARG)
			count++;
		index++;
	}
	return (count);
}

int	do_var_existe(t_token **arr_tok, int len, char **env)
{
	int		i;
	int 	y;
	int 	count;
	char	*str;
	t_token *temp;
	
	count = 0;
	y = 0;
	temp = *arr_tok;
	while (y < len)
	{
		while (y < len && temp[y].type >= RED_OUT && temp[y].type <= RED_HERE_DOC)
			y +=2;
		if (y == len)
			break ;
		if (temp[y].type == PIPE)
			y++;
		temp[y].subst = 0;
		i = 0;
		while (env[i])
		{
			str = ft_var_only(env[i]);
			if ((ft_strcmp(temp[y].value, "$?") == 0) || (temp[y].type == DOLLAR && ft_strcmp(str, temp[y].value + 1) == 0) || ((*(temp[y].value) == '$') && !*(temp[y].value + 1)))
			{
				count++;
				temp[y].subst = 1;
			}
			else if (temp[y].type == ARG)
			{
				count++;
				free(str);
				break ;
			}
			free(str);
			i++;
		}
		if (temp[y].type == DOLLAR && temp[y].subst == 0)
		{
			free(temp[y].value);
			temp[y].value = NULL;
		}
		y++;
	}
	return (count);
}

char	**ft_fill_args(t_token *arr_tok, int index, int len, char **env, int ret)
{
	char	**args;
	char	*temp;
	char	*temp1;
	int		nbr_args;
	int		i;

	(void)ret; //utiliser pour expand $?
	i = 0;
	nbr_args = do_var_existe(&arr_tok, len, env);
	args = malloc(sizeof(char *) * (nbr_args + 1));
	if (args == (void *)0)
		return ((void *)0);
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT && arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (((arr_tok[index].type == DOLLAR && arr_tok[index].subst == 1) || arr_tok[index].type == ARG))
		{
			args[i] = ft_expand_dollar(arr_tok[index].value, arr_tok[index].fl_quotes, env, ret);//expand si dollar ou args=arr.value si arg
			// printf("args[i] = %s\n", args[i]);
			while ((((arr_tok[index].fl_space == 0 && (arr_tok[index + 1].fl_quotes == 2 || arr_tok[index + 1].fl_quotes == 1)) 
			&& index < (len - 1)) || ((arr_tok[index].fl_space == 0 && arr_tok[index + 1].fl_quotes == 0) && index < (len - 1)))
			&& ((arr_tok[index + 1].type < 5) || (arr_tok[index + 1].type > 8)))
			{
				// write(1, "jfjfj\n", 6);
				temp = ft_expand_dollar(arr_tok[index + 1].value, arr_tok[index + 1].fl_quotes, env, ret);
				temp1 = args[i];
				if (temp != NULL)
				{
					args[i] = ft_strjoin(temp1, temp);
					free(temp1);
				}
				// printf("args1[i] = %s\n", args[i]);
				free(temp);
				index++;
			}
			i++;
		}
		index++;
	}
	args[i] = (void *)0;
	return (args);
}
