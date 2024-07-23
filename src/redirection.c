/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:34:34 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/23 15:34:35 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

// For STDIN redirections -1 if file doesnt exists, -2 if file not allowed
int	make_redir(int i, int pfd[], int *p_out)
{
	t_list	*temp;
	int		x;
	int		fd_o;
	int		fd_i;

	(void)pfd;
	fd_o = -1;
	fd_i = -1;
	temp = _ms(0)->tokenized_prompt;
	x = 0;
	while (x != i)
	{
		if (ft_strcmp("SIMPLE_|", ((t_quote *)temp->content)->token) == 0)
			x++;
		temp = temp->next;
	}
	while (temp && ft_strcmp(((t_quote *)temp->content)->token,
			"SIMPLE_|") != 0)
	{
		if (ft_strncmp("SIMPLE_>", ((t_quote *)temp->content)->token, 8) == 0)
		{
			if (access(((t_quote *)temp->next->content)->str, F_OK) == 0)
				if (access(((t_quote *)temp->next->content)->str, W_OK) == -1)
					ft_pexit(1);
			fd_o = open(((t_quote *)temp->next->content)->str,
					O_CREAT | O_TRUNC | O_RDWR, 0644);
		}
		else if (ft_strncmp("DOUBLE_>", ((t_quote *)temp->content)->token,
				8) == 0)
		{
			if (access(((t_quote *)temp->next->content)->str, F_OK) == 0)
				if (access(((t_quote *)temp->next->content)->str, W_OK) == -1)
					ft_pexit(1);
			fd_o = (close(fd_o), open(((t_quote *)temp->next->content)->str,
						O_CREAT | O_APPEND | O_WRONLY, 0644));
		}
		else if (ft_strncmp("SIMPLE_<", ((t_quote *)temp->content)->token,
				8) == 0)
		{
			if (access(((t_quote *)temp->next->content)->str, F_OK) != 0)
				ft_pexit(1);
			if (access(((t_quote *)temp->next->content)->str, R_OK) != 0)
				ft_pexit(1);
			fd_i = (close(fd_i), open(((t_quote *)temp->next->content)->str,
						O_RDONLY));
		}
		else if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token,
				8) == 0)
		{
			fd_i = (close(fd_i), open(ft_strjoin("/tmp/",
							ft_itoa(((t_quote *)temp->next->content)->id)),
						O_RDONLY));
		}
		temp = temp->next;
	}
	if (fd_o != -1)
	{
		if (pfd)
			pfd[1] = fd_o;
		else
			dup2(fd_o, STDOUT_FILENO);
	}
	if (fd_i != -1)
		*p_out = fd_i;
	return (1);
}
