/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 10:59:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_bin(t_simple_command *c_table, char **env)
{
    pid_t   child;
    char    **path;
    int     status;
    
    path = ft_get_paths(env); //check access
    ft_add_path(c_table, path);
    child = fork();
    if (child < 0)
        return (perror("Fork"));
    if (child == 0)
    {
        execve(c_table->args[0], c_table->args, env);
        perror("Error");
    }
    waitpid(child, &status, 0);
}