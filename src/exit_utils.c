/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:12:15 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/31 00:09:32 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	forked;

	forked = fork();
	if (forked == -1)
		ft_exit(NULL, NULL);
	return (forked);
}

void	check_if_null(char *str)
{
	if (!str)
		ft_exit("Malloc Error", NULL);
}
