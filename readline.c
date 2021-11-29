#include "./minishell.h"

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
	char *cmd;
	t_token *arr_tok;
	char **temp_env;
	t_simple_command *c_table;
	int	temp_ret;
	int nbr_tokens;
	int i;

	c_table = NULL;
	temp_ret = 0;
	temp_env = ft_copy_env(env);
	i = 0;
	if (ac != 1 || !av[0])
		return (printf("No arguments!!!!!!!\n"));
	while (1)
	{
		cmd = readline(PROMPT);
		// char test[] = "\"$USER $USER\"";
		if (cmd == NULL)
		{
			// rl_clear_history();
			ft_free_2dstr(temp_env);
			return (temp_ret); //return valeur de la derneire commande
		}
		// printf("%s\n", cmd);
		arr_tok = ft_split_tokens(cmd);
		// printf("%s\n", cmd);
		// arr_tok = ft_split_tokens(test);
		// printf("%s\n", arr_tok[0].value);
		// int nbr = nbr_words(cmd);
		// printf("%d\n", nbr);
		nbr_tokens = nbr_words(cmd);
		// printf("%d\n", nbr_tokens);
		while (i < nbr_tokens)
		{
			printf("token = %s; fl_space = %d, fl_quotes = %d\n", arr_tok[i].value, arr_tok[i].fl_space, arr_tok[i].fl_quotes);
			i++;
		}
		printf("nbr words = %d\n", nbr_tokens);
		typification(arr_tok, nbr_tokens);
		c_table = creation_list_command(arr_tok, nbr_tokens, temp_env);
		// i = 0;
		// while (i < nbr_tokens)
		// {
		// 	printf("arg = %s\n", c_table->args[i]);
		// 	i++;
		// }
		// c_table = ft_get_simple_command(cmd, temp_env); //doit creer liste chainee
		// free(cmd);
		// /////// piping
		// // cmd = readline("cmd pipe ");
		// // c_table->next = ft_get_simple_command(cmd, temp_env);
		// // c_table->next->previous = c_table;
		// // c_table->next->next = NULL;
		// // c_table->previous = NULL;
		// // free(cmd);
		// // ft_pipe(c_table);
		// // return (0);
		// /////////////////////
		if (c_table == NULL)
		{
			free(cmd);
			return (0);
		}
        if (c_table->infile == -42000 || c_table->outfile == -42000)
            return (printf("wrong infile outfile : %d", c_table->badfd));
		ft_pipe(c_table);
		add_history(cmd);
		temp_env = c_table->env;
		temp_ret = c_table->last_ret;
		ft_proper_free(c_table);
		c_table = NULL;
		free(cmd);///res de readline a free
	}
	// rl_clear_history();
	return (0);
}
