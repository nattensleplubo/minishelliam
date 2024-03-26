#include "./includes/minishell.h"

t_minishell *_ms(int params)
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

void init_ms(void)
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
