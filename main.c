/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/27 14:35:01 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell *
_ms(int params) // Global function 1 to print it's values. 0 To do nothing
{
  static t_minishell *ms = NULL;
  (void)params;

  if (!ms) {
    ms = malloc(sizeof(t_minishell));
    if (!ms)
      exit(0);
  }
  return (ms);
}

void init_ms(void) // Initialize all values to some default ones at the
                   // beginning of the program
{
  _ms(0)->prompt = NULL;
}

int main(int argc, char **argv, char **envp)
{
  (void)argc;
  (void)argv;
  init_env(envp);
  print_tab(_ms(0)->env);
  init_ms();
  while (9) {
    read_line();
    _ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
    printf("%d\n", get_index_of_varname(_ms(0)->prompt));
    printf("%s\n", get_value_of_varname(_ms(0)->prompt));
  }
}
