/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:48 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/22 16:14:23 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exec_builtins(char **prompt)
{
	if (ft_strcmp(prompt[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(prompt[0], "echo") == 0)
		return (ft_echo(prompt));
	else if (ft_strcmp(prompt[0], "env") == 0)
		return (print_tab(_ms(0)->env));
	else if (ft_strcmp(prompt[0], "export") == 0)
		return (ft_export(prompt));
	else if (ft_strcmp(prompt[0], "unset") == 0)
		return (ft_unset(prompt));
	else if (ft_strcmp(prompt[0], "cd") == 0)
		return (ft_cd(prompt + 1));
	else if (ft_strcmp(prompt[0], "exit") == 0)
		return (ft_exit("", prompt));
	else
		return (0);
}

int	ft_error_check(char *prompt)
{
	struct stat	path_stat;

	if (access(prompt, F_OK) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ft_pexit(127);
	}
	else if (stat(prompt, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(" Is a directory\n", 2);
		ft_pexit(126);
	}
	else if (access(prompt, X_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		ft_pexit(126);
	}
	return (1);
}

void	pipe_error_code(void)
{
	if (WIFEXITED(_ms(0)->status))
		_ms(0)->errnum = WEXITSTATUS(_ms(0)->status);
	else
		_ms(0)->errnum = -1;
}

int	ft_search(char **prompt, char **path)
{
	int		i;
	char	*full_path;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/\0", prompt[0]);
	while (path && path[i])
	{
		full_path = ft_strjoin(path[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, prompt, _ms(0)->env);
			free(full_path);
			free(cmd);
			free_tab(path);
			ft_pexit(-1);
		}
		else
			errno = 127;
		free(full_path);
		i++;
	}
	free(cmd);
	ft_putstr_fd(" command not found\n", 2);
	return (0);
}

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
