#include "../includes/minishell.h"

void read_line(void)
{
  free(_ms(0)->prompt);
  _ms(0)->prompt = readline("shell $ ");
  if (!_ms(0)->prompt)
  {
    rl_clear_history();
    printf("exit\n");
    exit(0);
  }
  if (strlen(_ms(0)->prompt) != 0) //! REPLACE BY LIBFT FUNCTION
    add_history(_ms(0)->prompt);
}
