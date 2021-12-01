/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:05:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/01 12:42:29 by cbeaurai         ###   ########.fr       */
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
		return (printf("No arguments!!!!!!!\n"));
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
			arr_tok = ft_split_tokens(cmd);
			nbr_tokens = nbr_words(cmd);
			typification(arr_tok, nbr_tokens);
			c_table = creation_list_command(arr_tok, nbr_tokens, temp_env, temp_ret);
			// c_table->last_ret = temp_ret;
			if (c_table == NULL)
			{
				free(cmd);
				return (0);
			}
			if (c_table->infile == -42000 || c_table->outfile == -42000)
				c_table->last_ret = 1;
			else
				c_table->last_ret = ft_pipe(c_table);
			add_history(cmd);
			temp_env = c_table->env;
			temp_ret = c_table->last_ret;
			ft_proper_free(c_table);
			c_table = NULL;
		}
		free(cmd);///res de readline a free
	}
	rl_clear_history();
	return (0);
}
