/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:04:34 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 15:41:47 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "libft/libft.h"

int	exit_free_val(char *cmd, int ret)
{
	if (cmd)
		free(cmd);
	exit(ret);
}

int	soft_quit(char **temp_env, int ret)
{
	rl_clear_history();
	ft_free_2dstr(temp_env);
	return (ret);
}

int	ft_2dlen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (-1);
	while (tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}

int	launch_start(char *cmd, int nbr_tok, char ***env, int ret)
{
	t_token				*arr_tok;
	t_simple_command	*c_table;

	arr_tok = ft_split_tokens(cmd, nbr_tok);
	if (check_syntax(arr_tok, nbr_tok))
	{
		c_table = creation_list_command(arr_tok, nbr_tok, *env, ret);
		if (c_table == NULL)
			exit_free_val(cmd, 0);
		if (c_table->infile == -42000 || c_table->outfile == -42000
			|| c_table->args_num == 0)
			c_table->last_ret = 1;
		else
			c_table->last_ret = ft_pipe(c_table);
		env = &c_table->env;
		ret = c_table->last_ret;
		ft_proper_free(c_table);
		c_table = NULL;
	}			
	else
		ret = 2;
	add_history(cmd);
	return (ret);
}
