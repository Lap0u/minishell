#include "./minishell.h"

int	main(int ac, char **av, char **env)
{	
	char *cmd;
	t_simple_command *c_table;

	c_table = NULL;
	if (ac != 1 || !av[0])
		return (printf("No arguments!!!!!!!\n"));
	while (1)
	{
		cmd = readline(PROMPT);
		if (cmd == NULL)
			return (ft_proper_free(c_table)); ///return valeur de la derniere commande 
		c_table = ft_get_simple_command(cmd, env);
		if (c_table == NULL)
		{
			free(cmd);
			return (0);
		}
		if (ft_isbuiltin(c_table->cmd))
			ft_split_builtin(c_table, env);
		else
			ft_exec_bin(c_table, env);
		add_history(cmd);
		ft_proper_free(c_table);
		c_table = NULL;
		free(cmd);///res de readline a free
	}
	return (0);
}
