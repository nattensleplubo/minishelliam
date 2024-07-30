/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:16:27 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/30 18:37:17 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int signo)
{
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
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_signal_cmd(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = ft_handle_signal_cmd;
	ctrl_c.sa_flags = 0;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	wait_for_all_children(pid_t childrenpid)
{
	int	i;

	i = 0;
	waitpid(childrenpid, &_ms(0)->status, 0);
	if (WIFEXITED(_ms(0)->status))
		_ms(0)->errnum = WEXITSTATUS(_ms(0)->status);
	else
		_ms(0)->errnum = -1;
	while (i < _ms(0)->forks - 1)
	{
		waitpid(-1, &_ms(0)->status, 0);
		i++;
	}
}
