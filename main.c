/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/30 17:58:53 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Global function 1 to print it's values. 0 To do nothing
t_minishell	*_ms(int params)
{
	static t_minishell	*ms = NULL;

	(void)params;
	if (!ms)
	{
		ms = malloc(sizeof(t_minishell));
		if (!ms)
			exit(0);
	}
	return (ms);
}

void	ft_free_prev_prompt(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (_ms(0)->splitted_prompt)
		free_tab(_ms(0)->splitted_prompt);
	if (_ms(0)->commands)
	{
		while (_ms(0)->commands[i])
		{
			while (_ms(0)->commands[i][j])
				free(_ms(0)->commands[i][j++]);
			free(_ms(0)->commands[i++]);
			j = 0;
		}
		free(_ms(0)->commands);
	}
	i = 0;
	if (_ms(0)->tokenized_prompt)
		ft_lstclear(&_ms(0)->tokenized_prompt, free_content);
	_ms(0)->commands = NULL;
	_ms(0)->splitted_prompt = NULL;
}

void	init_ms(void) // Initialize all values to some default ones at the
{
	_ms(0)->prompt = NULL;
	_ms(0)->splitted_prompt = NULL;
	_ms(0)->env = NULL;
	_ms(0)->tokenized_prompt = NULL;
	_ms(0)->commands = NULL;
	_ms(0)->forks = 0;
	_ms(0)->errnum = 0;
}

void	ft_bash(void)
{
	if (read_line())
	{
		expend_env_vars();
		_ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
		ft_token();
		delete_quotes();
		exec();
		if (check_token_grammar() != 0)
		{
			ft_free_prev_prompt();
			return ;
		}
		ft_pipe();
		ft_free_prev_prompt();
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	s;

	(void)argc;
	(void)argv;
	s.sa_handler = ft_signal;
	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	rl_catch_signals = 0;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	init_ms();
	init_env(envp);
	errno = 0;
	while (9)
	{
		sigaction(SIGINT, &s, NULL);
		ft_bash();
	}
}
