#include "../minishell.h"

int    sig_val(int ret)
{
	extern int g_signum;

    if (g_signum != -1)
    {
        ret = g_signum;
        g_signum = -1;
    }
    return (ret);
}

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
    write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    quithandler(int sig)
{
    extern int g_signum;
	(void)sig;
	write(0, "\b\b  \b\b", 6);
}

void    inthandler2(int sig)
{
    extern int g_signum;
	(void)sig;

    g_signum = 130;
    write(2, "\n", 1);
}

void    quithandler2(int sig)
{
    extern int g_signum;
	(void)sig;

    g_signum = 131;
	write(2, "Quit (core dumped)\n", 19);
}