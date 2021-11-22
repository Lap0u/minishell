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
    char    **path;

    path = ft_get_paths(env); //check access
    if (path == NULL)
    {
        printf(" %s : commande introuvable car PATH est unset\n", c_table->cmd);
        return ;
    } 
    ft_add_path(c_table, path);
    if (access(c_table->args[0], X_OK) == 0)
    {
       	int stdout;             //redir
        int stdin;                
        int ret;
            
        stdin = dup(STDIN_FILENO);
        stdout = dup(STDOUT_FILENO);
        if (c_table->outfile >= 0)
        {
            ret = dup2(c_table->outfile, STDOUT_FILENO);
            if (ret < 0)
                perror("Error");
        }
        if (c_table->infile >= 0)
        {
            ret = dup2(c_table->infile, STDIN_FILENO);
            if (ret < 0)
                perror("Error");
        }
        execve(c_table->args[0], c_table->args, env);
        perror("Error exec");
    	ret = dup2(stdout, STDOUT_FILENO);
        if (ret < 0)
                perror("Error");
    	ret = dup2(stdin, STDIN_FILENO);
        if (ret < 0)
                perror("Error");
    }
    else
    {
        execve(c_table->args[0], c_table->args, env);
        perror("Error");        
    }
}