#include "../includes/minishell.h"

void fill_list(void) {
  int i;
  int size;
  t_list *temp;

  temp = _ms(0)->tokenized_prompt;
  size = tab_size(_ms(0)->splitted_prompt);
  i = 0;
  while (i < size) {
    printf("%d\n", i);
    ((t_quote *)temp->content)->str =
        ft_calloc(sizeof(char), ft_strlen(_ms(0)->splitted_prompt[i]));
    ft_strlcpy(((t_quote *)temp->content)->str, _ms(0)->splitted_prompt[i],
               ft_strlen(_ms(0)->splitted_prompt[i]) + 1);
    i++;
    temp = temp->next;
  }
}

int get_number_of_commands(void) {
  t_list *temp;
  int i;

  i = 0;

  temp = _ms(0)->tokenized_prompt;
  while (temp) {
    if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3)) {
      i++;
    }
    temp = temp->next;
  }
  return i;
}

int get_number_of_args(int i) {
  int ret_size;
  int j;
  t_list *temp;

  j = 0;
  ret_size = 1;
  temp = _ms(0)->tokenized_prompt;
  while (j != i) {
    if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3))
      j++;
    temp = temp->next;
  }
  while (!ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3) && temp) {
    if (ft_strncmp(((t_quote *)temp->content)->token, "arg", 3))
      ret_size++;
    temp = temp->next;
  }
  return ret_size;
}

char ***make_commands_tab() {
  char ***ret;
  int ints[5]; // 0: cmd, 1: i, 2: tab_size, 3 fill_commands
  t_list *temp;

  temp = _ms(0)->tokenized_prompt;
  ints[1] = 0;
  ints[0] = get_number_of_commands();
  ret = malloc(sizeof(char **) * (ints[0] + 1));
  ret[ints[0]] = NULL;
  while (ints[1] < ints[0]) {
    if (ft_strncmp(((t_quote *)temp->content)->token, "cmd", 3)) {
      ints[3] = 1;
      ints[2] = get_number_of_args(ints[1]);
      ret[ints[1]] = malloc(sizeof(char *) * (ints[2] + 1));
      ret[ints[1]][ints[2]] = NULL;
      ft_strlcpy(ret[ints[1]][0], ((t_quote *)temp->content)->str,
                 ft_strlen(((t_quote *)temp->content)->str));
      ints[1]++;
    }
    if (ft_strncmp(((t_quote *)temp->content)->token, "arg", 3))
      ft_strlcpy(ret[ints[1]][ints[3]++], ((t_quote *)temp->content)->str,
                 ft_strlen(((t_quote *)temp->content)->str));
    temp = temp->next;
  }
  return ret;
}

void exec(void) {
  fill_list();
  ft_lstprint(_ms(0)->tokenized_prompt);
  // _ms(0)->commands = make_commands_tab();
}
