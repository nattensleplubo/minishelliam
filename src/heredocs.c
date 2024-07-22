#include "../includes/minishell.h"

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
			printf("id : %d\n", ((t_quote *)temp->content)->id);
			heredoc_loop(((t_quote *)temp->next->content)->str,
				((t_quote *)temp->next->content)->id);
		}
		temp = temp->next;
	}
}