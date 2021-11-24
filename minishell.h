#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
// # include "./libft/libft.h" //a commenter pour compiler parser/lexer
# include <limits.h> 
# include "libft/libft.h" 


# define PROMPT ">minishell "

//type 0 = output, type 1 = input, type 2 = output_append, type 3 = here_doc

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_simple_command
{
	int		args_num;//
	char	**args;//
	char	*cmd;//
	char	**env;
	int		last_ret;
	int 	infile;
	int 	outfile;
	int		badfd;
	t_redir	*redir;
	struct s_simple_command *next;
	struct s_simple_command *previous;
}				t_simple_command;

t_simple_command	*ft_get_simple_command(char *str, char **env);

int	ft_strcmp(char *s1, char *s2);

int	ft_isbuiltin(char *str);

char	*ft_get_command(char *str);

char	**ft_get_args(char *str, char **env);

int ft_get_args_size(char **args);

void	ft_split_builtin(t_simple_command **c_table);

void	ft_bi_echo(t_simple_command *c_table);

void	ft_bi_cd(t_simple_command *c_table);

void	ft_bi_pwd(t_simple_command *c_table);

void	ft_bi_export(t_simple_command **c_table);

void	ft_bi_unset(t_simple_command **c_table);

void	ft_bi_env(t_simple_command *c_table);

void	ft_bi_exit(t_simple_command *c_table);

void	ft_exec_bin(t_simple_command *c_table, char **env);

char	**ft_get_paths(char **envp);

char	*ft_add_slash(char *res);

char	*ft_rm_path(char *str);

void    ft_add_path(t_simple_command *c_table, char **path);

int		ft_proper_free(t_simple_command *c_table);

char	**ft_copy_env(char **env);

void	ft_open_files (t_simple_command *c_table, t_redir *list);

int		ft_pipe(t_simple_command *c_table);

void    ft_proccessing(t_simple_command *c_table, int *right, int *left);

void    ft_free_2dstr(char **str);
/*parsing*/

typedef struct s_token
{
	int		type;
	char	*value;
	int		fl_quotes;
	int		subst;
	int		fl_space;
}				t_token;

# define COMMANDE 1
# define FLAG 2
# define ARG 3
# define PIPE 4
# define RED_OUT 5 // > 
# define RED_IN 6 // <
# define RED_OUT_APP 7 // >>
# define RED_HERE_DOC 8 // <<
# define DOLLAR 9 // substitution


# define COMMANDE 1

/*parsing/lexer/ft_split_tokens.c*/
int		what_is_len_s_quotes(char *str);
int		what_is_len_double_quotes(char *str);
int		what_is_len_simple(char *str);
int		what_is_len(char *str);
char	*make_str(char *str);
void	make_str_dollar(char *str, t_token *my_arr, int *i, int *y);
void	make_str_s_quotes(char *str, t_token *my_arr, int *i, int *y);
void	check_str_double_quote(char *str, t_token *my_arr, int *i, int *y);
void	make_str_double_quote(char *str, t_token *my_arr, int *i, int *y);
void	make_str_simple(char *str, t_token *my_arr, int *i, int *y);
void	typification(t_token *my_arr, int nbr_token);
t_token	*ft_split_tokens(char *str);


/*parsing/lexer/nbr_tockens.c*/

int	ft_strlen(const char *s);
int		in_charset(char letter);
int		nbr_words_s_quotes(char const *str, int *i);
int		nbr_words_dollar(char const *str, int *i);
int		nbr_words_double_quotes(char const *str, int *i);
int		nbr_words(char const *str);


/*parsing/lexer/which_type_is_it.c*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		which_type(t_token *my_arr);
void	typification(t_token *my_arr, int nbr_token);

/*parsing/parser/preparsing.c*/
t_simple_command	*new_elem(t_token *arr_tok, int index, int len, char **env);
void	add_new_elem(t_simple_command **st, t_token *arr_tok, int ind, int len, char **env);
void	add_env_in_elem(t_simple_command *lst_command, char **env);
t_simple_command *creation_list_command(t_token *arr_tok, int arr_len, char **env);

/*parsing/parser/tools_parser.c*/
void	print_args(t_simple_command *start);
void	print_redir(t_simple_command *start);
void	ft_print_sentences(t_simple_command *start);
void	ft_free_3dtab(char **tab);
void	ft_free_redir(t_redir **list);
char	*ft_expand_dollar(char *str, int mode, char **env);
/*parsing/parser/fill_args_parser.c*/
int		ft_count_args(t_token *arr_tok, int index, int len);
char	**ft_fill_args(t_token *arr_tok, int index, int len, char **env);

/*parsing/parser/fill_redir_parser.c*/
int	is_there_red(t_token *arr_tok, int index, int len, char **env);
void	new_redir(t_token *arr_tok, t_redir **start);
t_redir	*ft_fill_redir(t_token *arr_tok, int index, int len, char **env);

/*parsing/parser/verif_parsing.c*/

int is_redir(t_token arr_tok);
int is_text(t_token arr_tok);
int nbr_pipe(t_token *arr_tok, int len);
int skip_topipe(t_token *arr_tok, int index, int len);
int		ft_2dlen(char **tab);

char	*ft_var_only(char *str);

#endif