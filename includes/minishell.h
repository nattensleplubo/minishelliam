#ifndef MINISHELL_H

# define MINISHELL_H

typedef struct s_minishell
{
  char *prompt;
  int i;
} t_minishell;

// INCLUDES 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// PROTOS
t_minishell *_ms(int params);
void read_line(void);

#endif
