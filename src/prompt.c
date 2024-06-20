/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:36 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/19 20:29:59 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char	*ft_stjoin(char *s1, char *s2, int tofree)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if(tofree == 0)
		free(s1);
	else if(tofree == 1)
		free(s2);
	return (dest);
}


int read_line(void) {
  char *path;
  char *line;
  int ret_val;

  ret_val = 0;
  path = NULL;
  path = getcwd(NULL, 2048);
  line = ft_stjoin(path, " $ ", 3);
  line = ft_stjoin("\033[0;36m", line ,1);
  line = ft_stjoin(line, "\e[0m", 0);
  if (_ms(0)->prompt)
    free(_ms(0)->prompt);
  _ms(0)->prompt = readline(line);
  if (!_ms(0)->prompt) 
  {
    rl_clear_history();
    printf("exit\n");
    ft_exit("CTRL - D");
  }
  if (ft_strlen(_ms(0)->prompt) != 0)
    ret_val = (add_history(_ms(0)->prompt), 1);
  return (free(path), free(line), ret_val);
}
