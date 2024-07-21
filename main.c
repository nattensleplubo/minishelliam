/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/19 16:21:22 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <time.h>

int	g_err = 0;

t_minishell	*_ms(int params) // Global function 1 to print it's values. 0 To do nothing
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
	{
		while (_ms(0)->splitted_prompt[i])
			free(_ms(0)->splitted_prompt[i++]);
		free(_ms(0)->splitted_prompt);
	}
	i = 0;
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

void	ft_lstprint(t_list *lst)
{
	t_list	*temp;

	printf("\033[0;33mTOKENIZED PROMPT :\n");
	if (lst == NULL)
		return ;
	temp = lst;
	printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
		((t_quote *)temp->content)->str);
	while (temp->next)
	{
		temp = temp->next;
		printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
			((t_quote *)temp->content)->str);
	}
	printf("----------------------------------------------\033[0m\n");
}

void	init_ms(void) // Initialize all values to some default ones at the
{
	_ms(0)->prompt = NULL; // beginning of the program
	_ms(0)->splitted_prompt = NULL;
	_ms(0)->env = NULL;
	_ms(0)->tokenized_prompt = NULL;
	_ms(0)->commands = NULL;
	_ms(0)->errnum = 0;
}

void	ft_bash(void)
{
	if (read_line())
	{
		expend_env_vars();
		_ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
		ft_token();
		if (check_token_grammar() != 0)
			return ;
		delete_quotes();
		exec();
		// ft_lstprint(_ms(0)->tokenized_prompt);
		ft_pipe();
		ft_free_prev_prompt();
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	s;


	s.sa_handler = ft_signal;
	sigemptyset(&s.sa_mask);  // Initialize the signal mask to empty
    s.sa_flags = 0;  
	rl_catch_signals = 0;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	init_ms();
	init_env(envp);
	errno = 0;
	if (argc > 2 && argv[1][0] && argv[1][1])
	{
		if(argv[1][0] == '-' && argv[1][1] == 'c')
		{
			_ms(0)->splitted_prompt = prompt_splitter(argv[2]);
			ft_token();
			// printf("%d\n", ft_lstsize(_ms(0)->tokenized_prompt));
			delete_quotes();
			// print_tab(_ms(0)->splitted_prompt);
			exec();
			ft_pipe();
			ft_free_prev_prompt();
			ft_exit("", NULL);
		}
	}
	while (9)
		ft_bash();
}
