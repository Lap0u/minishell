/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:51:59 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/10 11:09:59 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_wrong_file(void)
{
	write(2, "Error while opening file, exiting...\n", 38);
	exit(EXIT_SUCCESS);
}

void	ft_wrong_arg(void)
{
	write(2, "Error, wrong argument, exiting...\n", 35);
	exit(EXIT_SUCCESS);
}

void	ft_wrong_env(void)
{
	write(2, "Error, PATH variable couldn't be found, exiting...\n", 52);
	exit(EXIT_SUCCESS);
}

void	ft_wrong_malloc(void)
{
	write(2, "Error, malloc couldn't allocate memory accordingly, exiting...\n", 64);
	exit(EXIT_SUCCESS);
}
