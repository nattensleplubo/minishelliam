#include "../includes/minishell.h"

int init_env(char **env)
{
  int i;

  i = tab_size(env);
  _ms(0)->env = malloc(sizeof(char *) * (i + 1));
  if (!_ms(0)->env)
    return (0);
  i = 0;
  while (env[i])
  {
    _ms(0)->env[i] = ft_strdup(env[i]);
    i++;
  }
}

