#include "../includes/minishell.h"

void fill_list(void) {
  int i;
  int size;
  t_list *temp;

  temp = _ms(0)->tokenized_prompt;
  size = tab_size(_ms(0)->splitted_prompt);
  i = 0;
  while (i < size) {
    ft_strlcpy(((t_quote *)temp->content)->str, _ms(0)->splitted_prompt[i],
               ft_strlen(_ms(0)->splitted_prompt[i]));
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
  int ints[5]; // 0: cmd, 1: i, 2: tab_size, ...
  t_list *temp;

  temp = _ms(0)->tokenized_prompt;
  ints[1] = 0;
  ints[0] = get_number_of_commands(); // Calcul le nombre de commandes qu'il y
                                      // aura a executer
  ret = malloc(sizeof(char **) *
               (ints[0] + 1)); // Allocation de tableau de tableau de strings
  while (ints[1] <
         ints[0]) { // Tant que l'index est inferieur au nombre de commandes
    if (ft_strncmp(((t_quote *)temp->content)->token, "cmd",
                   3)) { // Si on tombe sur un commande
      ints[2] = get_number_of_args(
          ints[1]); // Calcul le nombre d'arguments d'une commande
      ret[ints[1]] = malloc(sizeof(char *) *
                            (ints[2] + 1)); // Allocation de tableau de strings
      ints[1]++;
    }
    temp = temp->next;
  }
  return ret;
}

void exec(void) {
  fill_list();
  make_commands_tab();
}
