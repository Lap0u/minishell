#include "minishell.h"
//comp avec -lreadline
#define B_SIZE 10
#define PROMPT ">minishell "
int	main()
{
	static char buffer[B_SIZE + 1];
	write(1, PROMPT, ft_strlen(PROMPT));
	read(0,  buffer, B_SIZE);
	buffer[B_SIZE] = 0;
	printf("%s\n", buffer);
	/*
	char *cmd;
	cmd = readline(">minishell ");
	printf("%s\n", cmd);
	add_history(cmd);
	free(cmd);///res de readline a free
	*/return (0);
}
