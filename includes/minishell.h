#ifndef O_TMPFILE
	#define _O_TMPFILE 020000000
	#define O_TMPFILE (_O_TMPFILE | O_DIRECTORY)
	#define O_TMPFILE_MASK (_O_TMPFILE | O_DIRECTORY | O_CREAT)
#endif

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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

typedef struct s_minishell {
  char *prompt;
  int i;
  char **splitted_prompt;
  char **env;
  char ***commands;
  t_list *tokenized_prompt;
  int	errnum;
  int	status;
} t_minishell;

typedef struct s_quote {
  char *str;
  char *token;
  int id;
} t_quote;

extern int g_err;

typedef enum {
    TOKEN_CMD,
    TOKEN_ARG,
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_FNM,
    TOKEN_UNKNOWN,
    TOKEN_COUNT
} TokenType;

typedef enum {
    STATE_START,
    STATE_AFTER_CMD,
    STATE_AFTER_PIPE,
    STATE_AFTER_REDIR,
    STATE_ERROR
} State;

// PROTOS
t_minishell *_ms(int params);
int read_line(void);
char **prompt_splitter(char const *s);
int print_tab(char **tab);
int tab_size(char **tab);
int ft_cd(char **dirtogo);
int ft_pwd(void);
int ft_exit(char *reason, char **prompt);
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
void	ft_pipe();
int	make_redir(int i, int pfd[], int *p_out);
int	ft_echo(char **cmd);
int	ft_export(char **arg);
int	ft_unset(char **arg);
int	ft_strcmp(const char *str1, const char *str2);
void free_content(void *content);
int	ft_pexit(int exit_number);
int check_quotes();
bool check_token_grammar();

#endif
