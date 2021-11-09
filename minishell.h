#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include <limits.h>

# define PROMPT ">minishell "

typedef struct s_simple_command
{
	int	args_num;
	char **args;
	char *cmd;
	char **env;
}				t_simple_command;

t_simple_command *ft_get_simple_command(char *str, char **env);

int	ft_strcmp(char *s1, char *s2);

int	ft_isbuiltin(char *str);

char	*ft_get_command(char *str);

char    **ft_get_args(char *str, char **env);

int ft_get_args_size(char **args);

void	ft_split_builtin(t_simple_command *c_table, char **env);

void	ft_bi_echo(t_simple_command *c_table);

void	ft_bi_cd(t_simple_command *c_table);

void	ft_bi_pwd(t_simple_command *c_table);

void	ft_bi_export(t_simple_command *c_table, char **str);

void	ft_bi_unset(t_simple_command *c_table);

void	ft_bi_env(t_simple_command *c_table, char **env);

void	ft_bi_exit(t_simple_command *c_table);

void	ft_exec_bin(t_simple_command *c_table, char **env);

char	**ft_get_paths(char **envp);

char	*ft_add_slash(char *res);

char	*ft_rm_path(char *str);

void    ft_add_path(t_simple_command *c_table, char **path);

#endif