#include "../minishell.h"


void    set_signals(void)
{
    signal(SIGINT, inthandler);
    signal(SIGQUIT, quithandler);
}

void    set_signals2(void)
{
    signal(SIGINT, inthandler2);
    signal(SIGQUIT, quithandler2);
}


void    inthandler(int sig)
{
    extern int    g_signum;
	(void)sig;

    g_signum = 130;
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    quithandler(int sig)
{
    extern int g_signum;
	(void)sig;
    g_signum = 131;
}

void    inthandler2(int sig)
{
    extern int g_signum;
	(void)sig;

    g_signum = 130;
    write(2, "\n", 1);
}

void    quithandler2(int sig)//a faire
{
    extern int g_signum;
	(void)sig;

    g_signum = 131;
	write(1, "Quit (core dumped)\n", 19);
}