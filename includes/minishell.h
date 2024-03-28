#ifndef MINISHELL_H

# define MINISHELL_H

// INCLUDES 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"


typedef struct s_minishell
{
  char *prompt;
  int i;
  char **splitted_prompt;
  char **env;
} t_minishell;

typedef struct s_quote
{
  char *str;
  char *token;
  struct t_quote *next;
} t_quote;

typedef struct s_env
{
  char *str;
  char *name;
  char *value;
  struct t_env *next;
} t_env;

// PROTOS
t_minishell *_ms(int params);
void read_line(void);
char	**prompt_splitter(char const *s);
void	print_tab(char **tab);
int	tab_size(char **tab);

#endif
