/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:16:27 by lzaengel          #+#    #+#             */
/*   Updated: 2024/04/24 19:11:54 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int signo)
{
	(void)signo;

	if(signo == SIGINT)
	{
		write(2, "\n", 1); // new line in bash
		rl_replace_line("", 0); // empty buffer
		rl_on_new_line(); // new line in rl
    	rl_redisplay();	//refresh readline visually
	}
}