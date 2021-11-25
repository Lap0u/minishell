/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:48:17 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/25 13:56:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_sorted(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_expformat(const char *str)
{
	int	i;

	i = 0;
	write(1, "export ", ft_strlen("export "));
	while (str[i] && str[i] != '=')
		write(1, &str[i++], 1);
	if (str[i] != 0)
	{
		write(1, &str[i++], 1);
		write(1, "\"", 1);
		while (str[i])
			write(1, &str[i++], 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	ft_export_noarg(t_simple_command *c_table)
{
	int		i;
	char	**sorted;

	i = 0;
	while (c_table->env[i])
		i++;
	sorted = malloc(sizeof(char *) * (i + 1));
	if (sorted == NULL)
		return; //null;
	ft_cp_env(sorted, c_table->env);
	ft_sort_sorted(sorted); //add quote apres egal??
	i = 0;
	while (sorted[i])
	{
		print_expformat(sorted[i]);
		free(sorted[i++]);
	}
	free(sorted);
}

void	ft_export_arg(t_simple_command **c_table)
{
	int	i;

	i = 1;
	while ((*c_table)->args[i] != NULL)
	{
		if (is_valid_export((*c_table)->args[i]) == 0)
			ft_export_add((*c_table)->args[i], c_table);
		i++;
	}
}

void	ft_bi_export(t_simple_command **c_table)
{
	if ((*c_table)->args_num == 1)
		ft_export_noarg(*c_table);
	else
		ft_export_arg(c_table);
}
