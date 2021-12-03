/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:15:31 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 12:17:33 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_args(t_simple_command *start)
{
	int	i;

	i = 0;
	printf("ARGS : ");
	while (start->args[i])
	{
		printf("%s\t", start->args[i++]);
	}
	printf("\n");
}

void	print_redir(t_simple_command *c)
{
	t_redir	*save;

	save = c->redir;
	printf("REDIR : 0 = out    1 = in    2 = out_append    3 = here_doc\n");
	while (c->redir)
	{
		printf("type : %d  vers file : %s\t", c->redir->type, c->redir->file);
		c->redir = c->redir->next;
	}
	printf("\n\n");
	c->redir = save;
}

void	ft_print_sentences(t_simple_command *start)
{
	int	i;

	i = 0;
	while (start)
	{
		printf("SENTENCE : %d\n\n", i++);
		printf("COMMANDE : %s\n", start->cmd);
		print_args(start);
		print_redir(start);
		printf("index : %d\n", start->pos);
		start = start->next;
	}
}

char	*ft_var_only(char *str)
{
	int		i;
	int		end;
	char	*res;

	i = 0;
	end = 0;
	while (str[end + 1] != '=' && str[end + 1])
		end++;
	if (str[end + 1] == 0)
		return (NULL);
	res = malloc(sizeof(char) * end + 2);
	if (res == NULL)
		return (NULL);
	while (i <= end)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_add_var(char *str)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	while ((ft_strncmp(str + i, "=", 1) != 0) && str[i])
		i++;
	i += 1;
	res = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	return (res);
}

char	*ft_expand_dollar(char *str, int mode, char **env, int ret)
{
	int		i;
	char	*temp;

	i = 0;
	if (str)
	{
		if ((str[0] != '$' || mode == 8 || mode == 1)
			|| (str[0] == '$' && !str[1]))
			return (str);
		if (ft_strcmp("$?", str) == 0)
		{
			free(str);
			return (ft_itoa(ret));
		}
		while (env[i])
		{
			temp = ft_var_only(env[i]);
			if (ft_strcmp(temp, str + 1) == 0)
			{
				free(temp);
				free(str);
				str = ft_add_var(env[i]);
				return (str);
			}
			free(temp);
			i++;
		}
	}
	return (NULL);
}

void	ft_free_redir(t_redir **list)
{
	t_redir	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->file);
		free(temp);
	}
	*list = NULL;
}
