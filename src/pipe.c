/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:16:35 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/29 12:11:48 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <time.h>


void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if(tab)
	{	
		while(tab[i])
			free(tab[i++]);
		free(tab);
	}
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

int	ft_strcmp(const char *str1, const char *str2) 
{
    while (*str1 && (*str1 == *str2)) 
	{
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int	ft_builtins(char **prompt, int exec) // exec=0 just checking, exec=1 executing
{
	if (ft_strcmp(prompt[0], "pwd") == 0) {
		if (exec == 1)
			return (ft_pwd());
		return (1);
	}
	else if (ft_strcmp(prompt[0], "echo") == 0) {
		if (exec == 1)
			return (ft_echo(prompt));
		return (1);
	}
	else if (ft_strcmp(prompt[0], "env") == 0) {
		if (exec == 1)
			return (print_tab(_ms(0)->env));
		return (1);
	}
	else if (ft_strcmp(prompt[0], "export") == 0) {
		if (exec == 1)
			return (ft_export(prompt));
		return (2);
	}
	else if (ft_strcmp(prompt[0], "unset") == 0) {
		if (exec == 1)
			return(ft_unset(prompt));
		return (2);
	}
	else if (ft_strcmp(prompt[0], "cd") == 0) {
		if (exec == 1)
			return (ft_cd(prompt + 1)); // Changer pour que ca renvoie la valeur renvoyee par cd quand ca sera fait
		return (2);
	}
	else if (ft_strcmp(prompt[0], "exit") == 0) {
		if (exec == 1)
			return(ft_exit("", prompt));
		return (2);
	}
	else
		return (0);
}

int	ft_search(char **prompt, char **path)
{
	int i;
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
			g_err = errno;
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

int ft_error_check(char *prompt)
{
	struct stat path_stat;

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

void	ft_exec(char **prompt, int i)
{
	(void)i;
	char	**path;
	char	*val;
	
	if (checkifpath(prompt[0]) == 1)
	{
		ft_error_check(prompt[0]);
		execve(prompt[0], prompt, _ms(0)->env);
		g_err = errno;
		ft_pexit (-1);
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
			ft_pexit (ft_builtins(prompt, 1));
	}
}

void	ft_last(char **prompt, int p_out, int i)
{
	pid_t	childrenpid;

	if (ft_builtins(prompt, 0) != 2) {
		childrenpid = fork();
		if (childrenpid == 0) // if we are in the children process
		{
			make_redir(i, NULL, &p_out);
			dup2(p_out, STDIN_FILENO); //  replace the standart input of the command by the output of the previous pipe
			close(p_out);
			ft_exec(prompt, i);
			ft_pexit(666);
		}
		else //if we are in the parent process
		{
			close(p_out);
			waitpid (childrenpid, &_ms(0)->status, 0);
			if (WIFEXITED(_ms(0)->status)) {
                _ms(0)->errnum = WEXITSTATUS(_ms(0)->status); // save the exit status of the child process
            } 
			else {
                _ms(0)->errnum = -1; // handle error or abnormal termination
            }
		}
	}
	else {
		_ms(0)->errnum = ft_builtins(prompt, 1);
		close(p_out);
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
		ft_pexit(666);
	}
	else //if we are in the parent process
	{
		close(*p_out);
		close(pfd[1]);
		*p_out = pfd[0]; //save the output of the pipe for the next command
	}
}

void	heredoc_loop(char *limiter, int i)
{
	char	*filename;
	int		fd;
	char	*index;
	char	*line;

	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (143)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, limiter) == 0)
			break;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (!line)
		free(line);
	(free(filename), free(index), close(fd));
}

void	write_heredocs(int i)
{
	t_list *temp;
	int x;

	temp = _ms(0)->tokenized_prompt;
	temp = _ms(0)->tokenized_prompt;
  	x = -1;
	
	while (x != i) {
		if (ft_strncmp("cmd", ((t_quote *)temp->content)->token, 3) == 0)
			x++;
		temp = temp->next;
	}
	while (temp && ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) != 0) {
		if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token, 8) == 0)
			heredoc_loop(((t_quote *)temp->next->content)->str, i);
		temp = temp->next;
	}
}

void	ft_pipe()
{
	int		prevpipe;
	int		i;
	char	***cmd;
	int j = 0;

	cmd = _ms(0)->commands;
	while (cmd[j])
		write_heredocs(j++);
	i = 0;
	prevpipe = dup (0);
	while (cmd[i])
	{
		if (cmd[i] && cmd[i + 1] != NULL)
			ft_pipe2 (cmd[i], &prevpipe, i);
		else if (cmd[i] && cmd[i + 1] == NULL)
			ft_last (cmd[i], prevpipe, i);
		i++;
	}
	
}
