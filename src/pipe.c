/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:16:35 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/30 18:35:39 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtins(char **prompt, int exec)
{
	if (exec == 1)
		return (ft_exec_builtins(prompt));
	if (ft_strcmp(prompt[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(prompt[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(prompt[0], "env") == 0)
		return (1);
	else if (ft_strcmp(prompt[0], "export") == 0)
		return (2);
	else if (ft_strcmp(prompt[0], "unset") == 0)
		return (2);
	else if (ft_strcmp(prompt[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(prompt[0], "exit") == 0)
		return (2);
	else
		return (0);
}

void	ft_exec(char **prompt, int i)
{
	char	**path;
	char	*val;

	(void)i;
	if (checkifpath(prompt[0]) == 1)
	{
		ft_error_check(prompt[0]);
		execve(prompt[0], prompt, _ms(0)->env);
		ft_pexit(-1);
	}
	else
	{
		if (ft_builtins(prompt, 0) == 0)
		{
			val = get_value_of_varname("PATH");
			path = ft_split(val, ':');
			ft_search(prompt, path);
			free(val);
			free_tab(path);
		}
		else
			ft_pexit(ft_builtins(prompt, 1));
	}
}

void	ft_last(char **prompt, int p_out, int i)
{
	pid_t	childrenpid;

	if (ft_builtins(prompt, 0) != 2)
	{
		_ms(0)->forks++;
		childrenpid = fork();
		if (childrenpid == 0)
		{
			make_redir(i, NULL, &p_out);
			dup2(p_out, STDIN_FILENO);
			close(p_out);
			ft_exec(prompt, i);
			ft_pexit(666);
		}
		else
		{
			close(p_out);
			wait_for_all_children(childrenpid);
		}
	}
	else
	{
		_ms(0)->errnum = ft_builtins(prompt, 1);
		close(p_out);
	}
}

void	ft_pipe2(char **prompt, int *p_out, int i)
{
	int		pfd[2];
	pid_t	childrenpid;

	pipe(pfd);
	_ms(0)->forks++;
	childrenpid = fork();
	if (childrenpid == 0)
	{
		make_redir(i, pfd, p_out);
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		dup2(*p_out, STDIN_FILENO);
		close(*p_out);
		ft_exec(prompt, i);
		ft_pexit(666);
	}
	else
	{
		close(*p_out);
		close(pfd[1]);
		*p_out = pfd[0];
	}
}

void	ft_pipe(void)
{
	int		prevpipe;
	int		i;
	char	***cmd;

	cmd = _ms(0)->commands;
	write_heredocs();
	i = 0;
	prevpipe = dup(0);
	ft_signal_cmd();
	while (cmd[i])
	{
		if (cmd[i] && cmd[i + 1] != NULL)
			ft_pipe2(cmd[i], &prevpipe, i);
		else if (cmd[i] && cmd[i + 1] == NULL)
			ft_last(cmd[i], prevpipe, i);
		i++;
	}
}
