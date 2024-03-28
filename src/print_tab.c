#include "../includes/minishell.h"

int	tab_size(char **tab)
{
  int i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

void	print_tab(char **tab)
{
  int size;
  int i;

  i = 0;
  size = tab_size(tab);
  while (i < size)
  {
    printf("%s\n", tab[i]);
    i++;
  }
}
