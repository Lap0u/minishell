#include "minishell.h"
//comp avec -lreadline
int	main()
{
	char *cmd;
	cmd = readline(">minishell ");
	printf("%s\n", cmd);
	free(cmd);///res de readline a free
	return (0);
}
