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
	char **temp_env;
	t_simple_command *c_table;
	int	temp_ret;

	c_table = NULL;
	temp_ret = 0;
	temp_env = ft_copy_env(env);
	if (ac != 1 || !av[0])
		return (printf("No arguments!!!!!!!\n"));
	while (1)
	{
		cmd = readline(PROMPT);
		if (cmd == NULL)
		{
			rl_clear_history();
			ft_proper_free(c_table);
			return (temp_ret); //return valeur de la derneire commande
		}
		c_table = ft_get_simple_command(cmd, temp_env);
		if (c_table == NULL)
		{
			free(cmd);
			return (0);
		}
		if (ft_isbuiltin(c_table->cmd))
			ft_split_builtin(&c_table);
		else	//les builtins et exec doivent renvoyer une valeur de retour pour $?
			ft_exec_bin(c_table, env);
		add_history(cmd);
		temp_env = c_table->env;
		temp_ret = c_table->last_ret;
		ft_proper_free(c_table);
		c_table = NULL;
		free(cmd);///res de readline a free
	}
	rl_clear_history();
	return (0);
}
