/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 10:59:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char    **ft_copy_env(char **env)
{
    int     i;
    int     j;
    char    **res;
    
    i = 0;
    j = 0;
    while (env[i])
        i++;
    res = malloc(sizeof(char*) * (i + 1));
    if (res == NULL)
        return (NULL);
    while (j < i)
    {
        res[j] = ft_strdup(env[j]);
        j++;
    }
    res[j] = NULL;
    return (res);
}