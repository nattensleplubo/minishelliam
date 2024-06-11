#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>


int make_heredoc(char *str) {
	(void)str;
	char	*path;

	path = getcwd(NULL, 2048);
	int fd = open(path , O_RDWR | __O_TMPFILE);
	free(path);
	return fd;
}

int	make_redir(int i, int pfd[], int *p_out) {
	(void)pfd;
	// (void)p_out;
	t_list	*temp;
	int		x;
	int		fd_o;
	int		fd_i;

	fd_o = -1;
	fd_i = -1;
	temp = _ms(0)->tokenized_prompt;
	x = -1;
	while (x != i) {
		if (ft_strncmp("cmd", ((t_quote *)temp->content)->token, 3) == 0)
			x++;
		temp = temp->next;
	}
	while (temp && ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) != 0) {
		if (ft_strncmp("SIMPLE_>", ((t_quote *)temp->content)->token, 8) == 0) {
			fd_o = open(((t_quote *)temp->next->content)->str, O_CREAT | O_TRUNC | O_RDWR, 0777);
		} else if (ft_strncmp("DOUBLE_>", ((t_quote *)temp->content)->token, 8) == 0) {
			fd_o = (close(fd_o), open(((t_quote *)temp->next->content)->str, O_CREAT | O_APPEND | O_WRONLY));
		} else if (ft_strncmp("SIMPLE_<", ((t_quote *)temp->content)->token, 8) == 0) {
			fd_i = (close(fd_i), open(((t_quote *)temp->next->content)->str, O_RDONLY));
		} else if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token, 8) == 0) {
			fd_i = (close(fd_i), make_heredoc(((t_quote *)temp->next->content)->str));
		}
		temp = temp->next;
	}
	if (fd_o != -1) {
		if (pfd)
			pfd[1] = fd_o;
		else
		 	dup2(fd_o, STDOUT_FILENO);
	}
	if (fd_i != -1)
		*p_out = fd_i;
	return 1;
}