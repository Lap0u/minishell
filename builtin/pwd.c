/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:29 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/25 13:57:23 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bi_pwd(t_simple_command *c_table)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX))
	{
		perror("Error");
		c_table->last_ret = 1;//quelle val
	}
	else
		printf("%s\n", wd);
	(void)c_table;
}
