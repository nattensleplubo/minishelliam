#include "../includes/minishell.h"

int init_env(char **env)
{
  int i;
  int j;
  char *curr;
  t_list new;

  i = 0;
  while (env[i])
  {
    j = 0;
    while (env[i][j] != '=')
      j++;
    curr = malloc(sizeof(char) * j + 1);
    if (!curr)
      exit(0);
    j = 0;
    while (env[i][j] != '=')
    {
      curr[j] = env[i][j];
      j++;
    }
    curr[j] = '\0';
    new = malloc(sizeof(t_list));
    if (!new)
      exit(0);
  }
}
