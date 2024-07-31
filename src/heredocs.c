/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:50:50 by ngobert           #+#    #+#             */
/*   Updated: 2024/07/30 23:49:30 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*heredoc_join(char *index)
{
	char	*filename;

	filename = ft_strjoin("/tmp/", index);
	if (!filename)
	{
		free(index);
		ft_exit("Malloc Error", NULL);
	}
	return (filename);
}

void	heredoc_loop(char *limiter, int i)
{
	char	*filename;
	int		fd;
	char	*index;
	char	*line;

	index = ft_itoa(i);
	check_if_null(index);
	filename = heredoc_join(index);
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		(free(filename), free(index), ft_exit("Error Open", NULL));
	while (143)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (!line)
		free(line);
	(free(filename), free(index), close(fd));
}

void	write_heredocs(void)
{
	t_list	*temp;

	temp = _ms(0)->tokenized_prompt;
	while (temp)
	{
		if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token, 8) == 0)
		{
			heredoc_loop(((t_quote *)temp->next->content)->str,
				((t_quote *)temp->next->content)->id);
		}
		temp = temp->next;
	}
}
