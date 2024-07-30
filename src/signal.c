/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:16:27 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/30 18:03:32 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int signo)
{
	(void)signo;
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_signal_cmd(int signo)
{
	(void)signo;
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_signal_cmd()
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = ft_handle_signal_cmd;
	ctrl_c.sa_flags = 0;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}
