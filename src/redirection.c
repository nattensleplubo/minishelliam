#include "../includes/minishell.h"

// void	heredoc_loop(char *str, int fd)
// {
// 	int		i;
// 	char	*tmp;

// 	// ft_lstprint(_ms(0)->tokenized_prompt);

// 	i = 0;
// 	while (i == 0)
// 	{
// 		tmp = readline("> ");
// 		if (!tmp)
// 		{
// 			printf("WARNING\n");
// 			break ;
// 		}
// 		if (ft_strcmp(tmp, str) == 0)
// 			i++;
// 		else
// 		{
// 			write(fd, tmp, ft_strlen(tmp));
// 			write(fd, "\n", 1);
// 		}
// 	}
// }

// int make_heredoc(char *str) {
// 	// int fd = open("/tmp" , O_TMPFILE | O_RDWR | O_EXCL, 0600);
// 	int fd = open("/tmp/heredoc_output.txt", O_RDWR | O_CREAT | O_TRUNC,
// 0600); 	printf("%d\n", fd); 	heredoc_loop(str, fd); 	close(fd); 	return fd;
// }


int make_redir(int i, int pfd[], int *p_out) {
  (void)pfd;
  // (void)p_out;
  t_list *temp;
  int x;
  int fd_o;
  int fd_i;

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
      fd_o = open(((t_quote *)temp->next->content)->str,
                  O_CREAT | O_TRUNC | O_RDWR, 0644);
    } else if (ft_strncmp("DOUBLE_>", ((t_quote *)temp->content)->token, 8) ==
               0) {
      fd_o = (close(fd_o), open(((t_quote *)temp->next->content)->str,
                                O_CREAT | O_APPEND | O_WRONLY, 0644));
    } else if (ft_strncmp("SIMPLE_<", ((t_quote *)temp->content)->token, 8) == 0) {
      fd_i =
          (close(fd_i), open(((t_quote *)temp->next->content)->str, O_RDONLY));
    } else if (ft_strncmp("DOUBLE_<", ((t_quote *)temp->content)->token, 8) == 0) {
		fd_i = (close(fd_i), open(ft_strjoin("/tmp/", ft_itoa(i)), O_RDONLY));
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
