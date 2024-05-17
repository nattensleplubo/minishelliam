/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/04/09 18:38:41 by lzaengel         ###   ########.fr       */
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
  _ms(0)->splitted_prompt = NULL;
  _ms(0)->env = NULL;
}

int main(int argc, char **argv, char **envp) {
  (void)argc;
  (void)argv;
  init_ms();
  init_env(envp);
  while (9) {
    read_line();
    expend_env_vars();
    _ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
    print_tab(_ms(0)->splitted_prompt);
    printf("NEW PROMPT = `%s`\n", _ms(0)->prompt);
    // delete_quotes(); // TODO
  }
}
