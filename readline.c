/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:05:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 10:45:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		ft_check_space(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] > 32 && str[i] != 127)
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_ctable(t_simple_command **list, char **env)
{
	*list = malloc(sizeof(t_simple_command));
	if (*list == NULL)
		return ;
	(*list)->env = ft_copy_env(env);
	return ;
}

int	syntax_error(t_token *arr_token, int size, char *error)
{
	int i;

	i = 0;
	while (i < size)
		free(arr_token[i++].value);
	free(arr_token);
	write(2, "minishell: syntax error near unexpected token `", 48);
	write(2, error, ft_strlen(error));
	write(2, "'\n", 3);
	return (0);
}

int check_syntax(t_token *arr_tok, int nbr_tokens)
{
	int	i;

	i = 0;
	while (i < nbr_tokens)
	{
		if (arr_tok[0].value[0] == '|')
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		if (arr_tok[nbr_tokens - 1].value[0] == '|')
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		if ((arr_tok[i].value[0] == '|') && ((arr_tok[i - 1].value[0] == '<') || (arr_tok[i - 1].value[0] == '>')))
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		if (arr_tok[i].type >= RED_OUT && arr_tok[i].type <= RED_HERE_DOC && i + 1 == nbr_tokens)
			return (syntax_error(arr_tok, nbr_tokens, "newline"));
		if (arr_tok[i].type >= RED_OUT && arr_tok[i].type <= RED_HERE_DOC && 
			arr_tok[i + 1].type >= RED_OUT && arr_tok[i + 1].type <= RED_HERE_DOC)
			return (syntax_error(arr_tok, nbr_tokens, arr_tok[i + 1].value));
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{	
	char				*cmd;
	t_token				*arr_tok;
	char				**temp_env;
	t_simple_command	*c_table;
	int					temp_ret;
	int					nbr_tokens;

	c_table = NULL;
	temp_ret = 0;
	if (ac != 1 || !av[0])
		return (write(2, "No arguments for this beauty\n", 30));
	temp_env = ft_copy_env(env);
	while (1)
	{
		cmd = readline(PROMPT);
		if (cmd == NULL)
		{
			rl_clear_history();
			ft_free_2dstr(temp_env);
			return (temp_ret); //return valeur de la derneire commande
		}
		else if (ft_check_space(cmd) == 1)
		{
			nbr_tokens = nbr_words(cmd);
			printf("nbr = %d\n", nbr_tokens);
			if (nbr_tokens >= 0)
			{
				arr_tok = ft_split_tokens(cmd, nbr_tokens);
				typification(arr_tok, nbr_tokens);
				if (check_syntax(arr_tok, nbr_tokens))
				{
					c_table = creation_list_command(arr_tok, nbr_tokens, temp_env, temp_ret);
					if (c_table == NULL)
					{
						free(cmd);
						return (0);
					}
					if (c_table->infile == -42000 || c_table->outfile == -42000 || c_table->args_num == 0)
						c_table->last_ret = 1;
					else
						c_table->last_ret = ft_pipe(c_table);
					temp_env = c_table->env;
					temp_ret = c_table->last_ret;
					ft_proper_free(c_table);
					c_table = NULL;
				}
				else
					temp_ret = 2;
				add_history(cmd);
			}
		}
		free(cmd);///res de readline a free
	}
	rl_clear_history();
	return (0);
}
