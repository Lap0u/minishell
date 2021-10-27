#include "./minishell.h"

int	main(int ac, char **av, char **env)
{	
	char *cmd;
	t_simple_command *c_table;

	if (ac != 1 || !av[0])
		return (printf("No arguments!!!!!!!\n"));
	while (1)
	{
		cmd = readline(PROMPT);
		c_table = ft_get_simple_command(cmd);
		if (c_table == NULL)
		{
			free(cmd);
			return (0);
		}
		if (ft_isbuiltin(c_table->cmd))
			ft_split_builtin(c_table, env);
		//else execve
		add_history(cmd);
		free(cmd);///res de readline a free
	}
	return (0);
}
