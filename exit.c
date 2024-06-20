/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:37:01 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/19 20:51:08 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_exit(char *reason)
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
		while(_ms(0)->commands[i])
		{
			
			while(_ms(0)->commands[i][j])
			{
				free(_ms(0)->commands[i][j++]);
			}
			free(_ms(0)->commands[i++]);
		}
		free(_ms(0)->commands);
	}
	if (_ms(0)->tokenized_prompt)
		ft_lstclear(&_ms(0)->tokenized_prompt, free_content);
	printf("%s", reason);
	exit (errno);
}