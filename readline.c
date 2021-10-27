#include "minishell.h"
#define PROMPT ">minishell "


int	main()
{	
	char *cmd;
	t_simple_command *c_table;

	while (1)
	{
		cmd = readline(PROMPT);
		c_table = ft_get_simple_command(cmd);
		if (c_table == NULL)
		{
			free(cmd);
			return (0);
		}
		printf("%s\n", c_table->cmd);
		for (int i = 0; i < 2; i++)
			printf("arg: %s \n", c_table->args[i]);
		//if (ft_isbuiltin(c_table))
		//	ft_split_builtin(c_table);
		//else execve
		add_history(cmd);
		free(cmd);///res de readline a free
	}
	return (0);
}
