#include "./includes/minishell.h"

t_minishell *_ms(int params) // Global function 1 to print it's values. 0 To do nothing
{
  static t_minishell *ms = NULL;
  (void)params;

  if (!ms)
  {
    ms = malloc(sizeof(ms));
    if (!ms)
      exit(0);
  }
  return (ms);
}

void init_ms(void) // Initialize all values to some default ones at the beginning of the program
{
  _ms(0)->prompt = NULL;
}

int main(void)
{
  init_ms();
  while (9)
  {
    read_line();
    printf("prompt : %s\n", _ms(0)->prompt);
  }
}
