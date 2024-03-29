/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:36 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/27 12:20:37 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void read_line(void)
{
  char *path;
  char *line;

  path = NULL;
  path = getcwd(NULL, 100);
  line = ft_strjoin(path, " $ ");
  free(_ms(0)->prompt);
  _ms(0)->prompt = readline(line);
  if (!_ms(0)->prompt)
  {
    rl_clear_history();
    printf("exit\n");
    exit(0);
  }
  if (strlen(_ms(0)->prompt) != 0) //! REPLACE BY LIBFT FUNCTION
    add_history(_ms(0)->prompt);
  free(path);
  free(line);
}
