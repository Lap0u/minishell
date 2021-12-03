/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:25 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 13:25:18 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_noarg(t_simple_command *c_table)
{
	int	i;

	i = 0;
	while (c_table->env[i])
	{
		if (ft_strncmp("HOME=", c_table->env[i], 5) == 0)
		{
			if (chdir(&c_table->env[i][5]) < 0)
			{
				c_table->last_ret = 1;
				write(2, "minishell: cd: ", 16);
				write(2, &c_table->env[i][5], ft_strlen(&c_table->env[i][5]));
				perror(" ");
			}
			else
				c_table->last_ret = 0;
			return ;
		}
		i++;
	}
	write(2, "minishell: cd: HOME not set\n", 29);
	c_table->last_ret = 1;
}

char	*make_pwd(char *prefix)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX))
	{
		perror("minishell: error");
		return (NULL);
	}
	if (prefix)
		return (ft_strjoin(prefix, wd));
	else
		return (ft_strdup(wd));
}

void	cd_curpath(t_simple_command *c_table)
{
	int	ret;

	ret = chdir(c_table->args[1]);
	if (ret == -1)
	{
		c_table->last_ret = 1;
		write(2, "minishell: cd: ", 16);
		write(2, c_table->args[1], ft_strlen(c_table->args[1]));
		perror(" ");
	}
	else
		c_table->last_ret = 0;
}

void	cd_classic(t_simple_command *c_table)
{
	char	*temp;
	int		i;
	char	**path;

	i = 0;
	while (c_table->env[i] && ft_strncmp(c_table->env[i],
			"CDPATH=", ft_strlen("CDPATH=")))
		i++;
	if (c_table->env[i] == NULL)
	{
		cd_curpath(c_table);
		return ;
	}
	temp = ft_strjoin("/", c_table->args[1]);
	path = ft_split(&c_table->env[i][7], ':');
	i = 0;
	if (cd_path(c_table, path, temp) == 0)
		cd_curpath(c_table);
}

void	ft_bi_cd(t_simple_command *c_table)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = make_pwd("OLDPWD=");
	if (c_table->args_num > 2)
	{
		write(2, "minishell: cd: trop d'arguments\n", 33);
		c_table->last_ret = 1;
	}
	else if (c_table->args_num <= 1)
		cd_noarg(c_table);
	else if (c_table->args[1][0] == '/' || c_table->args[1][0] == '.')
		cd_curpath(c_table);
	else
		cd_classic(c_table);
	if (c_table->last_ret != 0)
	{
		free(oldpwd);
		return ;
	}
	newpwd = make_pwd("PWD=");
	add_pwds(c_table, oldpwd, newpwd);
}
