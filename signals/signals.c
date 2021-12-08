#include "../minishell.h"
# include <signal.h>
#include <sys/types.h>
# include "../libft/libft.h"


#define _XOPEN_SOURCE 700

int pid = 0;

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*b_prim;

	b_prim = (char *)b;
	i = 0;
	while (i < len)
	{
		b_prim[i] = c;
		i++;
	}
	return (b);
}

void	sig_ctrlc(int signo, siginfo_t *info, void *uap)
{
	(void)info;
	(void)uap;
	int id;

	id = getpid();
	if (signo == SIGINT)
	{
		printf("pid = %d, info->si_pid = %d\n", pid, id);
		if (id == pid)
		{
			printf("execution parent\n");
			usleep(300);
			
		}
		else
		{
			kill(id, SIGINT);
		}
		return ;
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			set;
	int ret;
	int lala;

	pid = getpid();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sig_ctrlc;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sa.sa_mask = set;
	sigaction(SIGINT, &sa, 0);
	ret = fork();
	if (ret == 0)
	{
		printf("insert number ;\n");
		scanf("%d", &lala);
		usleep(4);
	}
	else
	{
		printf("je suis parent\n");
		wait(NULL);
	}
	
	// while(1)
	// 	;
	return (0);
}
