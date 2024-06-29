/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:15:28 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/27 17:57:18 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	ft_backn(char **cmd)
{
	int	i[2];
	int	backn;

	backn = 1;
	i[0] = 1;
	if(!cmd[i[0]] || !cmd[i[0]][0])
		return (0);
	while (cmd[i[0]][0] == '-' && cmd[i[0]][1] == 'n' && backn  == i[0])
	{
		i[1] = 2;
		backn++;
		while (cmd[i[0]][i[1]])
		{
			if (cmd[i[0]][i[1]] != 'n')
			{
				backn --;
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
	return (backn);
}

void	ft_echo(char **cmd)
{
	int	backn;
	int i;

	backn = ft_backn(cmd);
	i = backn;
	while (cmd[i])
	{
		if (i > backn)
			write(1, " ", 1);
		ft_putstr_fd(cmd[i], 1);
		i++;
	}
	if (backn == 1)
		write(1, "\n", 1);
}