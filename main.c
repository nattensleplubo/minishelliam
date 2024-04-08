/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/04/08 19:01:26 by lzaengel         ###   ########.fr       */
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

void	ft_bash(void)
{
	char	*line;

	read_line();
    line = get_value_of_varname(_ms(0)->prompt);
    _ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
	//fprint_tab(_ms(0)->splitted_prompt);
    if (line) {
      printf("%d\n", get_index_of_varname(_ms(0)->prompt));
      printf("%s\n", get_value_of_varname(_ms(0)->prompt));
      free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	struct sigaction s;
	(void)argc;
  	(void)argv;
  	s.sa_handler = ft_signal;
	rl_catch_signals = 0;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	init_env(envp);
	init_ms();
	while (9)
	{
		ft_bash();
	}
}
