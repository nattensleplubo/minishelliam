/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:48:58 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/30 23:56:44 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

t_list	*move_to_command(int i, int *fd_i, int *fd_o)
{
	t_list	*temp;
	int		x;

	x = 0;
	*fd_i = -1;
	*fd_o = -1;
	temp = _ms(0)->tokenized_prompt;
	while (x != i)
	{
		if (ft_strcmp("SIMPLE_|", ((t_quote *)temp->content)->token) == 0)
			x++;
		temp = temp->next;
	}
	return (temp);
}

int	do_output_redir(t_list *temp, int fd)
{
	int	fd_o;

	fd_o = fd;
	if (ft_strncmp("SIMPLE_>", ((t_quote *)temp->content)->token, 8) == 0)
	{
		if (access(((t_quote *)temp->next->content)->str, F_OK) == 0)
			if (access(((t_quote *)temp->next->content)->str, W_OK) == -1)
				ft_pexit(1);
		fd_o = open(((t_quote *)temp->next->content)->str,
				O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else if (ft_strncmp("DOUBLE_>", ((t_quote *)temp->content)->token, 8) == 0)
	{
		if (access(((t_quote *)temp->next->content)->str, F_OK) == 0)
			if (access(((t_quote *)temp->next->content)->str, W_OK) == -1)
				ft_pexit(1);
		fd_o = open(((t_quote *)temp->next->content)->str,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (fd_o != fd && fd > 0)
		close(fd);
	if (fd_o == -1)
		ft_exit("Open Error", NULL);
	return (fd_o);
}

int	do_input_redir(t_list *temp, int fd)
{
	int		fd_i;
	char	*ito;
	char	*join;

	fd_i = fd;
	if (ft_strncmp("SIMPLE_<", ((t_quote *)temp->content)->token, 8) == 0)
	{
		if (access(((t_quote *)temp->next->content)->str, F_OK) != 0)
			ft_pexit(1);
		if (access(((t_quote *)temp->next->content)->str, R_OK) != 0)
			ft_pexit(1);
		fd_i = open(((t_quote *)temp->next->content)->str, O_RDONLY);
	}
	else if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token, 8) == 0)
	{
		ito = ft_itoa(((t_quote *)temp->next->content)->id);
		join = (check_if_null(ito), heredoc_join(ito));
		fd_i = open(join, O_RDONLY);
		fd_i = (free(ito), free(join), fd_i);
	}
	if (fd_i != fd && fd > 0)
		close(fd);
	if (fd_i == -1)
		ft_exit("Open Error", NULL);
	return (fd_i);
}

void	make_redir(int i, int pfd[], int *p_out)
{
	t_list	*temp;
	int		fd_o;
	int		fd_i;

	temp = move_to_command(i, &fd_i, &fd_o);
	while (temp && ft_strcmp(((t_quote *)temp->content)->token,
			"SIMPLE_|") != 0)
	{
		if (ft_strcmp("SIMPLE_>", ((t_quote *)temp->content)->token) == 0
			|| ft_strcmp("DOUBLE_>", ((t_quote *)temp->content)->token) == 0)
			fd_o = do_output_redir(temp, fd_o);
		if (ft_strcmp("SIMPLE_<", ((t_quote *)temp->content)->token) == 0
			|| ft_strcmp("DOUBLE_<", ((t_quote *)temp->content)->token) == 0)
			fd_i = do_input_redir(temp, fd_i);
		temp = temp->next;
	}
	if (fd_o != -1)
	{
		if (pfd)
			pfd[1] = fd_o;
		else
			ft_dup(fd_o, STDOUT_FILENO, NULL, 1);
	}
	if (fd_i != -1)
		*p_out = fd_i;
}
