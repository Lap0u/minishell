/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 14:43:32 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// extern struct sigaction	sa;
// extern sigset_t			set;

extern int pid;

void	execution(t_simple_command *c_table, char **env)
{
	// struct sigaction	sa;
	// sigset_t			set;

	// printf("execution enfant_exec\n");
	if (access(c_table->args[0], F_OK) == 0 && c_table->args[0] != 0) //FLAG pour fichier
	{
		if (c_table->outfile >= 0)
		{
			if (dup2(c_table->outfile, STDOUT_FILENO) < 0)
				perror("minishell :error");
		}
		if (c_table->infile >= 0)
		{
			if (dup2(c_table->infile, STDIN_FILENO) < 0)
				perror("minishell :error");
		}
		execve(c_table->args[0], c_table->args, env);
		perror("minishell :error execve");
		exit(127); //126 si nom de fichier ou dossier et perror different
	}
	else
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

void	ft_bin_nofork(t_simple_command *c_table, char **env)
{
	char	**path;

	path = ft_get_paths(env);
	if (path == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	ft_add_path(c_table, path);
	execution(c_table, env);
}

void	sig_ctrlc(int signo, siginfo_t *info, void *uap)
{
	(void)info;
	(void)uap;
	int id;

	id = getpid();
	if (id == pid)
	{
		if (signo == SIGINT)
		{
			printf("execution parent\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		else if (signo == SIGQUIT)
		{
			// printf("execution ctrlback\n");
			rl_redisplay();
			return ;
		}
	}
	else
	{
		if (signo == SIGINT)
		{
			printf("execution enfant\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
	
	}
}

// void	sig_ctrlc_enfant(int signo, siginfo_t *info, void *uap)
// {
// 	(void)info;
// 	(void)uap;
// 	int id;

// 	id = getpid();
// 	printf("execution enfant, id = %d\n", id);
// 	if (signo == SIGINT)
// 	{
// 		printf("execution enfant\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 		return ;
// 	}
// 	else if (signo == SIGQUIT)
// 	{
// 		// printf("execution ctrlback\n");
// 		rl_redisplay();
// 		return ;
// 	}
// }

void signal_ger(struct sigaction*sa, sigset_t *set)
{

	// printf("hello parent, id = %d\n", getpid());
	ft_memset(sa, 0, sizeof(sa));
	(*sa).sa_flags = SA_SIGINFO;
	(*sa).sa_sigaction = &sig_ctrlc;
	sigemptyset(set);
	sigaddset(set, SIGINT);
	sigaddset(set, SIGQUIT);
	(*sa).sa_mask = *set;
	sigaction(SIGINT, sa, 0);
	sigaction(SIGQUIT, sa, 0);	
}

// void signal_enfant(struct sigaction	*sa, sigset_t *set)
// {
// 	printf("hello enfant, id = %d\n", getpid());
// 	ft_memset(sa, 0, sizeof(sa));
// 	(*sa).sa_flags = SA_SIGINFO;
// 	(*sa).sa_sigaction = &sig_ctrlc_enfant;
// 	sigemptyset(set);
// 	sigaddset(set, SIGINT);
// 	sigaddset(set, SIGQUIT);
// 	(*sa).sa_mask = *set;
// 	sigaction(SIGINT, sa, 0);
// 	sigaction(SIGQUIT, sa, 0);
// }


void	ft_exec_bin(t_simple_command *c_table, char **env)
{
	char	**path;
	pid_t	child;

	// int id;
	struct sigaction	sa;
	sigset_t			set;

	// signal_parent(&sa, &set);
	// id = getpid();
	path = ft_get_paths(env);
	if (path == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, c_table->cmd, ft_strlen(c_table->cmd));
		write(2, ": No such file or directory\n", 29);
		c_table->last_ret = 127;
		return ;
	}
	ft_add_path(c_table, path);
	if (c_table->args_num != 0)
	{
		child = fork();
		if (child < 0)
			return (perror("minishell: fork : "));
		if (child == 0)
		{
			// id = getpid();
			// printf("pid_enf = %d\n", id);
			signal_ger(&sa, &set);
			execution(c_table, env);
		}
		else if (child > 0)
		{
			// id = getpid();
			// printf("pid = %d\n", id);
			// signal_ger(&sa, &set);
		}
		waitpid(child, &c_table->last_ret, 0);
		c_table->last_ret = WEXITSTATUS(c_table->last_ret);
	}
	else
		c_table->last_ret = 0;
}
