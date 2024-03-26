#ifndef MINISHELL_H

# define MINISHELL_H

typedef struct s_minishell
{
  char *prompt;
  int i;
  char **splitted_prompt;
} t_minishell;

typedef struct s_quote
{
  char *str;
  char *token;
  s_quote *next;
} t_quote;

// INCLUDES 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

# include "../libft42/libft.h"

// PROTOS
t_minishell *_ms(int params);
void read_line(void);

#endif
