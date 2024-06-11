/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:36 by lzaengel          #+#    #+#             */
/*   Updated: 2024/06/11 18:32:43 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int read_line(void) {
  char *path;
  char *line;
  int ret_val;

  ret_val = 0;
  path = NULL;
  path = getcwd(NULL, 2048);
  line = ft_strjoin(path, " $ ");
  line = ft_strjoin("\033[0;36m", line);
  line = ft_strjoin(line, "\e[0m");
  if (_ms(0)->prompt)
    free(_ms(0)->prompt);
  _ms(0)->prompt = readline(line);
  if (!_ms(0)->prompt) {
    rl_clear_history();
    printf("exit\n");
    exit(errno);
  }
  if (ft_strlen(_ms(0)->prompt) != 0)
    ret_val = (add_history(_ms(0)->prompt), 1);
  return (free(path), free(line), ret_val);
}
