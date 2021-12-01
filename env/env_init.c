/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/01 11:00:39 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	*ft_add_shlvl(char *env)
{
	int		i;
	int		lvl;
	char	*res;
	char	*temp;

	i = 6;
	lvl = ft_atoi(&env[i]);
	lvl++;
	temp = ft_itoa(lvl);
	res = ft_strjoin("SHLVL=", temp);
	free(temp);
	return (res);
}

char	**ft_empty_env()
{
	char **res;

	res = malloc(sizeof(char *) * 2);
	if (res == NULL)
		return (NULL);
	res[0] = ft_strdup(" ");
	res[1] = NULL;
	return (res);
}

char	**ft_copy_env(char **env)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (env[0] == NULL)
		return (ft_empty_env());
	while (env[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		return (NULL);
	while (j < i)
	{
		if (ft_strncmp("SHLVL=", env[j], ft_strlen("SHLVL=")) == 0)
			res[j] = ft_add_shlvl(env[j]);
		else
			res[j] = ft_strdup(env[j]);
		j++;
	}
	res[j] = NULL;
	return (res);
}
