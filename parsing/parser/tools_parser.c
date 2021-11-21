#include "../../minishell.h"

void	print_args(t_simple_command *start)
{
	int i;

	i = 0;
	printf("ARGS : ");
	while (start->args[i])
	{
		printf("%s\t", start->args[i++]);
	}
	printf("\n");
}

void	print_redir(t_simple_command *start)
{
	t_redir	*save;

	save = start->redir;
	printf("REDIR : 0 = out    1 = in    2 = out_append    3 = here_doc\n");
	while (start->redir)
	{
		printf("type : %d  vers file : %s\t", start->redir->type, start->redir->file);
		start->redir = start->redir->next;
	}
	printf("\n\n");
	start->redir = save;
}

void	ft_print_sentences(t_simple_command *start)
{
	int i;

	i = 0;
	while (start)
	{
		printf("SENTENCE : %d\n\n", i++);
		printf("COMMANDE : %s\n", start->cmd);
		print_args(start);
		print_redir(start);
		start = start->next;
	}
}

void	ft_free_3dtab(char **tab) //////a uncomment quand dollar sera implemente
{
	// int i;

	// i = 0;
	// if (!tab)
	// 	return ;
	// // while (tab[i])
	// // {
	// // 	free(tab[i]);
	// // 	i++;
	// // }
	free(tab);
}

void	ft_free_redir(t_redir **list)
{
	t_redir *temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		// free(temp.file); //a uncomment quand dollar sera imple
		free(temp);
	}
	*list = NULL;
}
