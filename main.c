/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:26 by lzaengel          #+#    #+#             */
/*   Updated: 2024/05/22 17:15:50 by lzaengel         ###   ########.fr       */
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

void ft_lstprint(t_list *lst) {
  printf("TOKENIZED PROMPT :\n");
  t_list *temp;

  if (lst == NULL)
    return;
  temp = lst;
  printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
         ((t_quote *)temp->content)->str);
  while (temp->next) {
    temp = temp->next;
    printf("TOKEN[%s]\t|\tCONTENT[%s]\n", ((t_quote *)temp->content)->token,
           ((t_quote *)temp->content)->str);
  }
  printf("----------------------------------------------\n");
}

void init_ms(void) // Initialize all values to some default ones at the
                   // beginning of the program
{
  _ms(0)->prompt = NULL;
  _ms(0)->splitted_prompt = NULL;
  _ms(0)->env = NULL;
  _ms(0)->tokenized_prompt = NULL;
}
void ft_bash(void) {
  if (read_line()) {

    expend_env_vars();
    _ms(0)->splitted_prompt = prompt_splitter(_ms(0)->prompt);
    // print_tab(_ms(0)->splitted_prompt);
    ft_token();
    // ft_lstprint(_ms(0)->tokenized_prompt);
    // printf("%d\n", ft_lstsize(_ms(0)->tokenized_prompt));
    delete_quotes();
    print_tab(_ms(0)->splitted_prompt);
    exec();
  }
}
int main(int argc, char **argv, char **envp) {
  (void)argc;
  (void)argv;
  struct sigaction s;
  (void)argc;
  (void)argv;
  s.sa_handler = ft_signal;
  rl_catch_signals = 0;
  sigaction(SIGINT, &s, NULL);
  sigaction(SIGQUIT, &s, NULL);
  init_ms();
  init_env(envp);
  while (9) {
    ft_bash();
  }
}
