#ifndef MINISHELL_H

#define MINISHELL_H

// INCLUDES
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_minishell {
  char *prompt;
  int i;
  char **splitted_prompt;
  char **env;
  char ***commands;
  t_list *tokenized_prompt;
} t_minishell;

typedef struct s_quote {
  char *str;
  char *token;
  int id;
} t_quote;

// PROTOS
t_minishell *_ms(int params);
int read_line(void);
char **prompt_splitter(char const *s);
void print_tab(char **tab);
int tab_size(char **tab);
void ft_cd(char *dirtogo);
void ft_pwd(void);
void ft_exit(char *reason);
void init_env(char **env);
int get_index_of_varname(char *varname);
char *get_value_of_varname(char *varname);
void expend_env_vars();
void delete_quotes(void);
int is_pipe(char c);
void ft_signal(int signo);
void ft_token(void);
void fill_list(void);
void exec(void);
void ft_lstprint(t_list *lst);
#endif
