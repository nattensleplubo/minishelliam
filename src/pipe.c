/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:16:35 by lzaengel          #+#    #+#             */
/*   Updated: 2024/04/11 18:59:52 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_pipe(char **prompt, int *p_out, char *path, char **env, int islast	)
{
	int		pfd[2];
	pid_t	childrenpid;

	pipe(pfd);
	childrenpid = fork();
	if(childrenpid == 0) // if we are in the children process
	{
		dup2(pfd[1], STDOUT_FILENO); //replace the standart ouput of the command by the input of the pipe
		if(islast == 0)
		{
			dup2(*p_out, STDIN_FILENO); //  replace the standart input of the command by the output of the previous pipe
			close(pfd[0]); // close the output of the pipe in the children process
		}
		close(*p_out); 
		execve(path, prompt, env); //execute the command
	}
	else //if we are in the parent process
	{
		close(*p_out);
		if(islast == 0)
		{
			close(pfd[1]);
			*p_out = pfd[0]; //save the output of the pipe for the next command
		}
	}
}

int ft_init_pipe(char **prompt, char *path, char **env)
{
	
}