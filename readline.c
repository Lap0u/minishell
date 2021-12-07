/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:05:36 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 16:54:54 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int pid = 0;
// struct sigaction	sa;
// sigset_t			set;

int	ft_check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] != 127)
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
	int	i;

	i = 0;
	if (error)
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		write(2, error, ft_strlen(error));
		write(2, "'\n", 3);
	}
	while (i < size)
		free(arr_token[i++].value);
	free(arr_token);
	return (0);
}

int	check_syntax(t_token *arr_tok, int nbr_tokens)
{
	int	i;

	i = 0;
	while (i < nbr_tokens)
	{
		if (arr_tok[0].type == PIPE)
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		else if (arr_tok[nbr_tokens - 1].type == PIPE)
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		else if (arr_tok[i].type == PIPE && arr_tok[i + 1].type == PIPE)
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		else if ((arr_tok[i].type == PIPE) && (arr_tok[i - 1].type >= RED_OUT
				&& arr_tok[i - 1].type <= RED_HERE_DOC))
			return (syntax_error(arr_tok, nbr_tokens, "|"));
		else if (arr_tok[i].type >= RED_OUT && arr_tok[i].type <= RED_HERE_DOC
			&& i + 1 == nbr_tokens)
			return (syntax_error(arr_tok, nbr_tokens, "newline"));
		else if (arr_tok[i].type >= RED_OUT && arr_tok[i].type <= RED_HERE_DOC
			&& arr_tok[i + 1].type >= RED_OUT
			&& arr_tok[i + 1].type <= RED_HERE_DOC)
			return (syntax_error(arr_tok, nbr_tokens, arr_tok[i + 1].value));
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{	
	char				*cmd;
	char				**temp_env;
	int					temp_ret;
	int					nbr_tokens;
	struct sigaction	sa;
	sigset_t			set;

	temp_ret = 0;
	pid = getpid();
	if (ac != 1 || !av[0])
		return (write(2, "No arguments for this beauty\n", 30));
	temp_env = ft_copy_env(env);
	while (1)
	{
		signal_ger(&sa, &set);
		// signal_parent(&sa, &set);
		cmd = readline(PROMPT);
		if (cmd == NULL)
			return (soft_quit(temp_env, temp_ret));
		else if (ft_check_space(cmd) == 1)
		{
			nbr_tokens = nbr_words(cmd);
			// printf("nbr = %d\n", nbr_tokens);//////debug
			add_history(cmd);
			if (nbr_tokens >= 0)
				launch_start(cmd, nbr_words(cmd),
						&temp_env, &temp_ret);
		}
		free(cmd);
	}
	rl_clear_history();
	return (0);
}
