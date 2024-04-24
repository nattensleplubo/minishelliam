/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:16:35 by lzaengel          #+#    #+#             */
/*   Updated: 2024/04/14 22:47:41 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_pipe(char **prompt, int len, int *p_out, char *path, char **env, int islast	)
{
	int		pfd[2];
	pid_t	childrenpid;

	pipe(pfd);
	childrenpid = fork();
	if(childrenpid == 0) // if we are in the children process
	{
		if(islast == 0)
		{
			close(pfd[0]); // close the output of the pipe in the children proces
			dup2(pfd[1], STDOUT_FILENO); //replace the standart ouput of the command by the input of the pipe
			close(pfd[1]);
		}
		dup2(*p_out, STDIN_FILENO); //  replace the standart input of the command by the output of the previous pipe
		close(*p_out); 
		prompt[len] = NULL;
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
		if (islast == 1)
		{
			while (wait (NULL) != -1)
				;
		}
	}
}

/*int ft_init_pipe(char **prompt, char *path, char **env)
{
	
}*/
int	ft_len(char	**cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|')
		len++;
	return (len);
}

int	main(int ac, char **cmd, char **env)
{
	int	prevpipe;
	int	len;

	(void)ac;
	len = 0;
	prevpipe = dup (0);
	while (cmd[len] && cmd[len + 1])
	{
		cmd += len + 1;
		len = ft_len (cmd);
		if (cmd[len] != NULL && *cmd[len] == '|')
			ft_pipe (cmd, len, &prevpipe, cmd[0], env, 0);
		else if (cmd[len] == NULL)
			ft_pipe (cmd, len, &prevpipe, cmd[0], env, 1);
	}
	return (0);
}	