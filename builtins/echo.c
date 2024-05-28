/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:15:28 by lzaengel          #+#    #+#             */
/*   Updated: 2024/05/28 16:16:14 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	ft_backn(char **cmd)
{
	int	i[2];
	int	backn;

	backn = 1;
	i[0] = 1;

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

/*
int main(int argc, char **argv) {
    // Example command arrays to test ft_echo
    // Each of these should simulate command line input to the echo command
    char *test_cmd1[] = {"echo", "-nnnnnnnnn", "Hello,", "world!", NULL};
    char *test_cmd2[] = {"echo", "-n", "-na", "Hello,", "world!", NULL};
    char *test_cmd3[] = {"echo", "Hello,", "world!", NULL};
    
    printf("Test 1:\n");
    ft_echo(test_cmd1);
    printf("Test 2:\n");
    ft_echo(test_cmd2);
    printf("Test 3:\n");
    ft_echo(test_cmd3);
    
    return 0;
}
*/