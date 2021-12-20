#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	kill(0, SIGSEGV);
	return (0);
}

// int main ()
// {
// 	char *str;
// 	str = malloc(sizeof(char) * 2);
// 	str[5] = 'r';
// 	printf("%s", str);
// 	return (0);
// }