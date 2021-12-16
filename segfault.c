#include <sys/types.h>
#include <signal.h>

int	main()
{
	kill(0, SIGSEGV);
	return (0);
}