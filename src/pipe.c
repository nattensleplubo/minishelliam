/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:16:35 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/11 17:17:02 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>

int	checkifpath(char *str)
{
	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	if (str[0] == '/')
		return (1);
	if (str[0] == '.' && (str[1] == '/' || (str[1] == '.' && str[2] == '/')))
		return (1);
	return (0);
}

int	ft_strcmp(const char *str1, const char *str2) 
{
    while (*str1 && (*str1 == *str2)) 
	{
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int	ft_builtins(char **prompt)
{
	if (ft_strcmp(prompt[0], "pwd") == 0)
	{}
	else if (ft_strcmp(prompt[0], "echo") == 0)
	{}
	else if (ft_strcmp(prompt[0], "env") == 0)
	{}
	else if (ft_strcmp(prompt[0], "export") == 0)
	{}
	else if (ft_strcmp(prompt[0], "unset") == 0)
	{}
	else if (ft_strcmp(prompt[0], "cd") == 0)
	{}
	else
		return (0);
	return (1);
}
int	ft_search(char **prompt, char **path)
{
	int i;
	char	*full_path;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/\0", prompt[0]);
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, prompt, _ms(0)->env);
			free(full_path);
			free(cmd);
			return(1);
		}
		i++;
	}
	free(cmd);
	return (0);
}

void	ft_exec(char **prompt, int i)
{
	(void)i;
	char	**path;
	
	if (checkifpath(prompt[0]) == 1)
	{
		if (access(prompt[0], X_OK) == 0)
		{
			execve(prompt[0], prompt, _ms(0)->env);
		}
		else
		{}
	}
	else
	{
		if(ft_builtins(prompt) == 0)
		{
			path = ft_split(get_value_of_varname("PATH"), ':');
			ft_search(prompt, path);
			free(path);
		}

	}
}

void	ft_last(char **prompt, int p_out, int i)
{
	pid_t	childrenpid;

	childrenpid = fork();
	if (childrenpid == 0) // if we are in the children process
	{
		make_redir(i, NULL, &p_out);
		dup2(p_out, STDIN_FILENO); //  replace the standart input of the command by the output of the previous pipe
		close(p_out);
		ft_exec(prompt, i);
		exit(0);
	}
	else //if we are in the parent process
	{
		close(p_out);
		while (wait (NULL) != -1)
			;
	}
}

void	ft_pipe2(char **prompt, int *p_out, int i)
{
	int		pfd[2];
	pid_t	childrenpid;

	pipe(pfd);
	childrenpid = fork();
	if (childrenpid == 0) // if we are in the children process
	{
		make_redir(i, pfd, p_out);
		close(pfd[0]); // close the output of the pipe in the children proces
		dup2(pfd[1], STDOUT_FILENO); //replace the standart ouput of the command by the input of the pipe
		close(pfd[1]);
		dup2(*p_out, STDIN_FILENO); //  replace the standart input of the command by the output of the previous pipe
		close(*p_out);
		ft_exec(prompt, i);
		exit(0);
	}
	else //if we are in the parent process
	{
		close(*p_out);
		close(pfd[1]);
		*p_out = pfd[0]; //save the output of the pipe for the next command
	}
}

void	ft_pipe()
{
	int		prevpipe;
	int		i;
	char	***cmd;

	cmd = _ms(0)->commands;
	i = 0;
	prevpipe = dup (0);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i + 1] != NULL)
		{
			ft_pipe2 (cmd[i], &prevpipe, i);
		}
		else if (cmd[i] && cmd[i + 1] == NULL)
		{
			ft_last (cmd[i], prevpipe, i);
		}
		i++;
	}
}
	