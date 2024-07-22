/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:37:01 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/22 15:32:17 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "libft/libft.h"

int	string_is_num(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] && (arg[0] == '-' || arg[0] == '+'))
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_number_picker(char **prompt)
{
	int	exit_number;

	exit_number = 0;
	if (prompt[1] && prompt[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		exit_number = 1;
	}
	else if (prompt[1] && !string_is_num(prompt[1]))
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		exit_number = 2;
	}
	else if (prompt[1])
		exit_number = ft_atoi(prompt[1]);
	return (exit_number);
}

int	ft_exit(char *reason, char **prompt)
{
	int	exit_number;

	exit_number = 0;
	if (prompt)
		exit_number = exit_number_picker(prompt);
	if (_ms(0)->prompt)
		free(_ms(0)->prompt);
	if (_ms(0)->splitted_prompt)
		free_tab(_ms(0)->splitted_prompt);
	if (_ms(0)->commands)
		free_taboftab(_ms(0)->commands);
	if (_ms(0)->env)
		free_tab(_ms(0)->env);
	if (_ms(0)->tokenized_prompt)
		ft_lstclear(&_ms(0)->tokenized_prompt, free_content);
	free(_ms(0));
	printf("%s", reason);
	if (exit_number < 0)
		exit_number = 256 + exit_number;
	exit (exit_number);
}

int	ft_pexit(int exit_number)
{
	if (_ms(0)->prompt)
		free(_ms(0)->prompt);
	if (_ms(0)->splitted_prompt)
		free_tab(_ms(0)->splitted_prompt);
	if (_ms(0)->commands)
		free_taboftab(_ms(0)->commands);
	if (_ms(0)->env)
		free_tab(_ms(0)->env);
	if (_ms(0)->tokenized_prompt)
		ft_lstclear(&_ms(0)->tokenized_prompt, free_content);
	free(_ms(0));
	if (exit_number == 666)
		exit(errno);
	exit (exit_number);
}
